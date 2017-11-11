#include "MatrixProcessing.h"

#include <opencv2\calib3d.hpp>

cv::Point3f operator*(cv::Point3f point, cv::Mat & kern)
{
	cv::Point3f transformedPoint;
	std::vector<float*> newCoordinates;
	newCoordinates.push_back(&transformedPoint.x);
	newCoordinates.push_back(&transformedPoint.y);
	newCoordinates.push_back(&transformedPoint.z);

	std::vector<float> oldCoordinates;
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

namespace homogenous
{
	cv::Vec4f operator*(cv::Vec4f point, cv::Mat & kern)
	{
		cv::Vec4f res{ 0,0,0,0 };

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				res[i] += point[j] * kern.at<float>(j, i);
			}
		}
		return res;
	}
}

std::vector<cv::Point3f> applyKern(std::vector<cv::Point3f> points, cv::Mat& kern)
{
	std::vector<cv::Vec4f> pivotHomogenous;
	convertPointsToHomogeneous(points, pivotHomogenous);

	for (auto& i : pivotHomogenous)
	{
		i = homogenous::operator*(i, kern);
	}

	std::vector<cv::Point3f> pivotModified;
	convertPointsFromHomogeneous(pivotHomogenous, pivotModified);
	return pivotModified;
}