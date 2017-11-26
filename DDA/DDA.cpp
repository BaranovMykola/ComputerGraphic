#include "DDA.h"

#include <opencv2\imgproc.hpp>

#include <iostream>

using namespace cv;

void DDA(cv::Point2f A, cv::Point2f B, cv::Mat & img, bool info)
{
	auto r = 1;

	/*circle(img, A, r, Scalar::all(255), -1);
	circle(img, B, r, Scalar::all(255), -1);*/

	double steps = std::max(abs(A.x - B.x), abs(A.y - B.y));
	double dx = (B.x - A.x) / steps;
	double dy = (B.y - A.y) / steps;

	for (double i = 0; i < steps+1; i++)
	{
		img.at<Vec3b>(A) = Vec3b(0, 0, 255);
		if (info)
		{
			std::cout << "Plot " << A << std::endl;
		}	
		A.x += dx;
		A.y += dy;
	}
}

std::vector<cv::Point> getPointsOnCircle(cv::Point center, int r, int n, cv::Mat & img)
{
	if (!img.empty())
	{
		for (double t = 0; t < 2*CV_PI; t+=0.01)
		{
			Point p
			(
				std::sin(t)*r + center.x,
				std::cos(t)*r + center.y
			);

		}
	}

	std::vector<cv::Point> set;

	for (double t = 0; t < CV_2PI- CV_2PI / (2*n); t += CV_2PI/n)
	{
		double s = std::sin(t);
		double c = std::cos(t);
		Point p
		(
			std::rint(std::sin(t)*r + center.x),
			std::rint(std::cos(t)*r + center.y)
		);

		set.push_back(p);
	}

	auto p = set;
	for (auto i : p)
	{
		auto diff = i - center;
		auto j = i - diff * 2;
		//set.push_back(j);
		//img.at<Vec3b>(j) = Vec3b(255,255,0);
	}

	return set;
}
