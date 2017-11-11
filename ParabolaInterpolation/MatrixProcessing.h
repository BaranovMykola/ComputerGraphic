#pragma once
#include <opencv2\core.hpp>

cv::Point3f operator*(cv::Point3f point, cv::Mat & kern);

std::vector<cv::Point3f> applyKern(std::vector<cv::Point3f> points, cv::Mat& kern);

namespace homogenous
{
	cv::Vec4f operator*(cv::Vec4f point, cv::Mat & kern);
}