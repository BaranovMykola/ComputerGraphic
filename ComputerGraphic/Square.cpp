#include "Square.h"
#include <opencv2\imgproc.hpp>

using namespace cv;

Square::Square(Point pt0, Point pt1, Point pt2, Point pt3)
{
	points[0] = Point3i(pt0.x, pt0.y, 1);
	points[1] = Point3i(pt1.x, pt1.y, 1);
	points[2] = Point3i(pt2.x, pt2.y, 1);
	points[3] = Point3i(pt3.x, pt3.y, 1);
}


Square::~Square()
{
}

void Square::draw(cv::Mat & img)
{
	for (int i = 0; i < 4; i++)
	{
		line(img, Point(points[i].x, points[i].y), Point(points[(i + 1) % 4].x, points[(i+1)%4].y), Scalar(0, 0, 255), 10);
	}
}

void Square::move(int delt)
{
	for (int i = 0; i < 4; i++)
	{
		points[i].x += delt;
		points[i].y += delt;
	}
}

void Square::move(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		points[i].x += x;
		points[i].y += y;
	}
}

void Square::applyKernel(cv::Mat & kern)
{
	for (int i = 0; i < 4; i++)
	{
		points[i] = points[i] * kern;
	}
}

cv::Mat Square::buildRotationMatrix(float angle, Point center)
{
	int x = center.x;
	int y = center.y;
	Mat move = (Mat_<float>(3, 3) << 1, 0, 0,
			  0, 1, 0,
			  -x, -y, 1);

	Mat rotate = (Mat_<float>(3, 3) << cos(angle), sin(angle), 0,
				-sin(angle), cos(angle), 0,
				0, 0, 1);

	Mat moveBack = (Mat_<float>(3, 3) << 1, 0, 0,
			  0, 1, 0,
			  x, y, 1);

	Mat kernel = move*rotate*moveBack;
	return kernel;
}

cv::Point3i operator*(cv::Point3i p, cv::Mat & kern)
{
	Point3i res;
	/*res.x = kern.at<float>(0, 0)*p.x + kern.at<float>(Point(1, 0))*p.y + kern.at<float>(Point(2, 0));
	res.y = kern.at<float>(Point(1,0))*p.x + kern.at<float>(Point(1, 1))*p.y + kern.at<float>(Point(2, 1));
	res.z = kern.at<float>(0, 2)*p.x + kern.at<float>(Point(1, 2))*p.y + kern.at<float>(Point(2, 2));*/
	auto x1 = kern.at<float>(0, 0);
	auto x2 = kern.at<float>(1, 0);
	auto x3 = kern.at<float>(2, 0);
	//p.x += x3;
	res.x = p.x*x1 + p.y*x2 + x3;

	auto y1 = kern.at<float>(0, 1);
	auto y2 = kern.at<float>(1, 1);
	auto y3 = kern.at<float>(2, 1);
	//p.y += y3;
	res.y = p.x*y1 + p.y*y2 + y3;

	auto z1 = kern.at<float>(0, 2);
	auto z2 = kern.at<float>(1, 2);
	auto z3 = kern.at<float>(2, 2);
	res.z = p.x*z1 + p.y*z2 + z3;
	/*res.x -= x3;
	res.y -= y3;*/
	//res.z = 1;
	return res;

}
