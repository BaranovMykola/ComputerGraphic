#pragma once
#include <opencv2\core.hpp>

class Parabola
{
public:
	Parabola(double _a, double _b, double _c);
	Parabola(double _a);
	Parabola(cv::Point _a, cv::Point _b, cv::Point _c);
	~Parabola();
	void draw(cv::Mat img, int from, int to, cv::Vec3b color = cv::Vec3b::all(255))const;
	void draw_(cv::Mat img);
	double y_(double theta)const;
	double y(double x)const;
	static void drawAverage(cv::Mat& img, const Parabola par1, const Parabola par2, int from, int to, cv::Vec3b color = cv::Vec3b::all(255));
private:
	double a;
	double b;
	double c;
	double a_;
};