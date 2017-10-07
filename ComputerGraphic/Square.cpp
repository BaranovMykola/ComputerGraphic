#include "Square.h"
#include <opencv2\imgproc.hpp>
#include <vector>

using namespace cv;

Shape::Shape(Point pt0, Point pt1, Point pt2, Point pt3)
{
	points[0] = Point3i(pt0.x, pt0.y, 1);
	points[1] = Point3i(pt1.x, pt1.y, 1);
	points[2] = Point3i(pt2.x, pt2.y, 1);
	points[3] = Point3i(pt3.x, pt3.y, 1);
}

Shape::Shape(std::initializer_list<Point> lst)
{
	for (auto i : lst)
	{
		pointsVec.push_back(Point3i(i.x, i.y, 1));
	}
}


Shape::~Shape()
{
}

void Shape::draw(cv::Mat & img)
{
	/*for (int i = 0; i < 4; i++)
	{
		line(img, Point(points[i].x, points[i].y), Point(points[(i + 1) % 4].x, points[(i+1)%4].y), Scalar(0, 0, 255), 10);
	}*/

	for (int i = 0; i < pointsVec.size(); i++)
	{
		circle(img, Point(pointsVec[i].x, pointsVec[i].y), 12, randomColor(rng), -1);
		line(img, Point(pointsVec[i].x, pointsVec[i].y), Point(pointsVec[(i + 1) % pointsVec.size()].x, pointsVec[(i + 1) % pointsVec.size()].y), Scalar(0, 0, 255), 10);
	}
}

void Shape::applyKernel(cv::Mat & kern)
{
	/*for (int i = 0; i < 4; i++)
	{
		points[i] = points[i] * kern;
	}*/

	for (int i = 0; i < pointsVec.size(); i++)
	{
		pointsVec[i] = pointsVec[i] * kern;
	}
}

cv::Mat Shape::buildRotationMatrix(float angle, Point center)
{
	float rad = (CV_PI / 180.0) * (angle);
	int x = center.x;
	int y = center.y;
	Mat move = (Mat_<float>(3, 3) << 1, 0, 0,
			  0, 1, 0,
			  -x, -y, 1);

	Mat rotate = (Mat_<float>(3, 3) << cos(rad), sin(rad), 0,
				-sin(rad), cos(rad), 0,
				0, 0, 1);

	Mat moveBack = (Mat_<float>(3, 3) << 1, 0, 0,
			  0, 1, 0,
			  x, y, 1);

	Mat kernel = move*rotate*moveBack;
	return kernel;
}

cv::Point3i operator*(cv::Point3i point, cv::Mat & kern)
{
	Point3i transformedPoint;
	std::vector<int*> newCoordinates;
	newCoordinates.push_back(&transformedPoint.x);
	newCoordinates.push_back(&transformedPoint.y);
	newCoordinates.push_back(&transformedPoint.z);

	std::vector<int> oldCoordinates;
	oldCoordinates.push_back(point.x);
	oldCoordinates.push_back(point.y);
	oldCoordinates.push_back(point.z);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			*newCoordinates[i] += oldCoordinates[j]* kern.at<float>(j, i);
		}
	}
	return transformedPoint;
}

static Scalar randomColor(RNG& rng)
{
	int icolor = (unsigned)rng;
	return Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

RNG Shape::rng = RNG();