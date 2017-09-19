#pragma once
#include <opencv2\core.hpp>
#include <vector>

static cv::Point3i operator*(cv::Point3i p, cv::Mat& kern);

class Square
{
public:
	Square(cv::Point pt0, cv::Point pt1, cv::Point pt2, cv::Point pt3);
	~Square();
	void draw(cv::Mat& img);
	void applyKernel(cv::Mat& kern);
	static cv::Mat buildRotationMatrix(float angle, cv::Point center);
private:
	cv::Vec<cv::Point3i, 4> points;
};

