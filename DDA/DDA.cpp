#include "DDA.h"

#include <opencv2\imgproc.hpp>

using namespace cv;

void DDA(cv::Point2f A, cv::Point2f B, cv::Mat & img)
{
	auto r = 3;

	circle(img, A, r, Scalar::all(255), -1);
	circle(img, B, r, Scalar::all(255), -1);

	double steps = std::max(abs(A.x - B.x), abs(A.y - B.y));
	double dx = (B.x - A.x) / steps;
	double dy = (B.y - A.y) / steps;

	for (double i = 0; i < steps; i++)
	{
		img.at<Vec3b>(A) = Vec3b(0, 0, 255);
		A.x += dx;
		A.y += dy;
	}
}
