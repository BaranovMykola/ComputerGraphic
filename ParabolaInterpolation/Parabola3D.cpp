#include "Parabola3D.h"
#include <opencv2\imgproc.hpp>

using namespace cv;

cv::Point3f operator*(cv::Point3f point, cv::Mat & kern)
{
	cv::Point3f transformedPoint;
	std::vector<float*> newCoordinates;
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
			*newCoordinates[i] += oldCoordinates[j] * kern.at<float>(j, i);
		}
	}
	return transformedPoint;
}

Parabola3D::Parabola3D(cv::Mat & _data)
{
	cv::Mat data_tp = cv::Mat(_data.cols, _data.rows, CV_32F);
	cv::transpose(_data, data_tp);
	data = data_tp;
}

Parabola3D::Parabola3D(cv::Point3f p1, cv::Point3f p2, cv::Point3f p3)
{
	cv::Mat P = (Mat_<float>(3, 3) << p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z);
	double a = a = norm(p2 - p1) / (norm(p3 - p2) + norm(p2 - p1));
	cv::Mat M = (Mat_<float>(3, 3) << 0, 0, 1, a*a, a, 1, 1, 1, 1);
	cv::Mat Mi;
	invert(M,Mi);
	cv::transpose(Mi*P,data);
}

Parabola3D::~Parabola3D()
{
}

void Parabola3D::draw(cv::Mat & img)
{
	double f = CV_PI/4;
	double theta = 33*CV_PI/180;

	cv::Mat kern = (cv::Mat_<float>(3, 3) << cos(f), sin(f)*sin(theta), -sin(f)*cos(theta),
					0, cos(theta), sin(theta),
					sin(f), -cos(f)*sin(theta), cos(f)*cos(theta));

	for (double t = 0; t < 1; t+=0.1)
	{
		cv::Point3f p(x(t), y(t), z(t));
		auto pers = p*kern;
		cv::circle(img, Point(p.x*100/2, p.y*10), 5, Scalar::all(255), 1);
	}
}

double Parabola3D::x(double t)
{
	float* row = data.ptr<float>(0);
	return row[0] * t*t + row[1] * t + row[2] ;
}

double Parabola3D::y(double t)
{
	float* row = data.ptr<float>(1);
	return row[0] * t*t + row[1] * t + row[2];
}

double Parabola3D::z(double t)
{
	float* row = data.ptr<float>(2);
	return row[0] * t*t + row[1] * t + row[2];
}


