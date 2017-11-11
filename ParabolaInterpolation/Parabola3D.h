#pragma once
#include <opencv2\core.hpp>

class Parabola3D
{
public:
	Parabola3D(cv::Mat& _data);
	Parabola3D(cv::Point3f p1, cv::Point3f p2, cv::Point3f p3);
	~Parabola3D();

	void draw(cv::Mat& img);
	double x(double t);
	double y(double t);
	double z(double t);

private:
	cv::Mat data;
};