#include "Parabola.h"

#include <opencv2/imgproc.hpp>


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
	}
}

void Parabola::draw_(cv::Mat img)
{
	double  h = 0.01;
	auto delt = std::pow(-1 * (1 / (2 * std::sqrt(a_))), 2);
	if (std::abs(delt) > 1)
	{
		delt = 1;
	}
	for (double i = 0; i < 1000;)
	{
		double theta = std::atan(std::sqrt(i));
		int y = 2 * std::sqrt(a_)*tan(theta);
		cv::Point pixel1(i, y);
		cv::Point pixel2(i, -y);
		i += std::abs(delt);
		if (i >= 0 && i < img.cols)
		{
			if (y < img.rows && y >= 0)
			{
				img.at<cv::Vec3b>(pixel1) = cv::Vec3b::all(255);
			}
			if (-y < img.rows && -y >= 0)
			{
				img.at<cv::Vec3b>(pixel2) = cv::Vec3b::all(255);
			}
		}
	}
}

double Parabola::y_(double theta) const
{
	return 0;
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
		Parabola::drawAverage(img, first, second, points[i].x, points[i + 1].x, nextColor());
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