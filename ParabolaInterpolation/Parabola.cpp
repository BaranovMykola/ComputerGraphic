#include "Parabola.h"

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <thread>

Parabola::Parabola(double _a, double _b, double _c) :
	a(_a),
	b(_b),
	c(_c)
{
}

Parabola::Parabola(double _a) :
	a_(_a)
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
	double h = 1/(1+b);
	h = std::abs(h) > 1 ? 1 : h;
	for (double i = from; i < to; i+=h)
	{
		auto y = this->y(i);
		if (y < img.rows && y >= 0)
		{
			cv::Point pixel(i, y);
			img.at<cv::Vec3b>(pixel) = color;
		}
		if (delay > 0 && (int)(i + h) != (int)i)
		{
			cv::imshow("draw", img);
			int response = cv::waitKey(delay);
			if (response == 27)
			{
				std::exit(0);
			}
		}
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
	for (double i = from; i < to; i += h)
	{
		auto y1 = par1.y(i);
		auto y2 = par2.y(i);
		auto y = (y1+y2) / 2;
		if (y < img.rows && y >= 0)
		{
			cv::Point pixel(i, y);
			img.at<cv::Vec3b>(pixel) = color;
		}
		if (delay > 0 && (int)(i+h) != (int)i)
		{
			cv::imshow("draw", img);
			int response = cv::waitKey(delay);
			if (response == 27)
			{
				std::exit(0);
			}
		}
	}
}

void Parabola::interpolate(cv::Mat & img, std::vector<cv::Point> points)
{
	std::sort(points.begin(), points.end(), [](auto i, auto j) { return i.x < j.x; });
	Parabola first(points[0], points[1], points[2]);
	first.draw(img, points[0].x, points[1].x, nextColor());
	for (int i = 1; i < points.size()-2; i++)
	{
		Parabola second(points[i], points[i+1], points[i + 2]);
		auto copy = img.clone();
		if (delay > 0)
		{
			first.draw(copy, points[i].x, points[i + 1].x, nextColor());
			second.draw(copy, points[i].x, points[i + 1].x, nextColor());
			Parabola::drawAverage(copy, first, second, points[i].x, points[i + 1].x, nextColor());
		}
		auto oldDelay = delay;
		delay = 0;
		first.draw(copy, 0, img.cols, nextColor());
		second.draw(copy, 0, img.cols, nextColor());
		cv::imshow("draw", copy);
		Parabola::drawAverage(img, first, second, points[i].x, points[i + 1].x, nextColor());
		delay = oldDelay;
		cv::waitKey(delay * 1000);
		first = second;
	}
	int last = points.size() - 1;
	Parabola end(points[last - 2], points[last - 1], points[last]);
	end.draw(img, points[last - 1].x, points[last].x, nextColor());
}

void Parabola::drawPoints(cv::Mat & img, std::vector<cv::Point> points)
{
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

int Parabola::delay = 0;

int Parabola::boost = 10;