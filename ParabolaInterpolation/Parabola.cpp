#include "Parabola.h"

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>


Parabola::Parabola(double _a, double _b, double _c) :
	a(_a),
	b(_b),
	c(_c)
{
}

Parabola::Parabola(cv::Point _a, cv::Point _b, cv::Point _c)
{
	cv::Mat A = (cv::Mat_<float>(3, 3) << std::pow(_a.x, 2), _a.x, 1,
				 std::pow(_b.x, 2), _b.x, 1,
				 std::pow(_c.x, 2), _c.x, 1);
	cv::Mat B = (cv::Mat_<float>(3, 1) << _a.y, _b.y, _c.y);

	cv::Mat A1;
	cv::invert(A, A1);

	cv::Mat X = A1*B;
	a = X.at<float>(0, 0);
	b = X.at<float>(1, 0);
	c = X.at<float>(2, 0);
}

Parabola::~Parabola()
{
}

void Parabola::draw(cv::Mat img, int from, int to, cv::Vec3b color) const
{
	double h = 1 / (1 + b);
	h = std::abs(h) > 1 ? 1 : std::abs(h);
	cv::Point last(from, y(from));
	for (double i = from; i < to + 0.5; i++)
	{
		auto y = this->y(i);
		cv::Point pixel(i, y);
		line(img, last, pixel, color, 1);
		last = pixel;
	}
}

double Parabola::y(double x) const
{
	return a*std::pow(x, 2) + b*x + c;
}

void Parabola::drawAverage(cv::Mat & img, const Parabola par1, const Parabola par2, int from, int to, cv::Vec3b color)
{
	double h1 = 1 / (1 + par1.a);
	h1 = std::abs(h1) > 1 ? 1 : h1;
	double h2 = 1 / (1 + par2.a);
	h2 = std::abs(h2) > 1 ? 1 : h2;
	auto h = std::min({ h1,h2 });
	cv::Point prev(from, (par1.y(from) + par2.y(from)) / 2);
	for (double i = from; i < to + 0.5; i++)
	{
		auto y1 = par1.y(i);
		auto y2 = par2.y(i);
		auto y = (y1 + y2) / 2;
		cv::Point pixel(i, y);
		line(img, prev, pixel, color, 1);
		prev = pixel;
	}
}

void Parabola::interpolate(cv::Mat & img, std::vector<cv::Point> points, int delay)
{
	if (points.size() < 3)
	{
		cv::putText(img, "Not enough points", cv::Point(img.rows / 4, img.cols / 10), CV_FONT_HERSHEY_COMPLEX, 3, cv::Scalar::all(255));
		return;
	}
	std::sort(points.begin(), points.end(), [](auto i, auto j) { return i.x < j.x; });
	Parabola first(points[0], points[1], points[2]);
	first.draw(img, points[0].x, points[1].x, nextColor());
	colorIndex--;
	for (int i = 1; i < points.size() - 2; i++)
	{
		Parabola second(points[i], points[i + 1], points[i + 2]);
		if (delay >= 0)
		{
			auto copy = img.clone();

			first.draw(copy, 0, img.cols, nextColor());
			cv::imshow("draw", copy);
			cv::waitKey(delay);

			second.draw(copy, 0, img.cols, nextColor());
			cv::imshow("draw", copy);
			cv::waitKey(delay);

			Parabola::drawAverage(copy, first, second, 0, img.cols, nextColor());
			cv::imshow("draw", copy);
			cv::waitKey(delay);

			auto der = 2 * second.a*points[i].x + second.b + 2 * first.a*points[i].x + first.b;
			cv::putText(img, std::to_string(der), points[i], CV_FONT_HERSHEY_COMPLEX, 0.5, nextColor());
			auto der2 = 2 * second.a*points[i + 1].x + second.b + 2 * first.a*points[i + 1].x + first.b;
			--colorIndex;
			cv::putText(img, std::to_string(der2), points[i + 1] - cv::Point(0, -60), CV_FONT_HERSHEY_COMPLEX, 0.5, nextColor());
		}
		--colorIndex;
		Parabola::drawAverage(img, first, second, points[i].x, points[i + 1].x, nextColor());
		if (delay >= 0)
		{
			cv::imshow("draw", img);
			cv::waitKey(delay);
		}
		first = second;
	}
	(--colorIndex)--;
	int last = points.size() - 1;
	Parabola end(points[last - 2], points[last - 1], points[last]);
	end.draw(img, points[last - 1].x, points[last].x, nextColor());
}

void Parabola::drawPoints(cv::Mat & img, std::vector<cv::Point> points)
{
	colorIndex = 0;
	for (auto i : points)
	{
		cv::circle(img, i, 6, nextColor(), -1);
	}
}

cv::Vec3b Parabola::nextColor()
{
	return colors[colorIndex++%colors.size()];
}

std::vector<cv::Vec3b> Parabola::colors{ cv::Vec3b(0,0,255), cv::Vec3b(0,255,0), cv::Vec3b(255,0,0),
										cv::Vec3b(255,0,255), cv::Vec3b(255,255,0), cv::Vec3b::all(255) };

int Parabola::colorIndex = 0;