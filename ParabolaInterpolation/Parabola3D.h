#pragma once
#include <opencv2\core.hpp>

class Parabola3D
{
public:
	Parabola3D(cv::Mat& _data);
	Parabola3D(cv::Point3f p1, cv::Point3f p2, cv::Point3f p3);
	~Parabola3D();

	void draw(cv::Mat& img);
	std::vector<cv::Point3f> plot(double h, double lowerBound, double upperBound);
	static std::vector<cv::Point3f> interpolate(std::vector<cv::Point3f> pivot, cv::Mat& img);
	static void draw(cv::Mat& img, std::vector<cv::Point3f> curve, std::vector<cv::Point3f> pivot, double f, double t, double x, double y);
	cv::Point3f take(double t);
	double x(double t);
	double y(double t);
	double z(double t);

private:
	cv::Mat data;
	double alpha;
};