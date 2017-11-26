#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

#include <iostream>

#include "DDA.h"

using namespace cv;

void butt(int state, void *userdata)
{
	std::cout << "clicked";
}

void on_trackbar(int, void* data)
{
	*(static_cast<bool*>(data)) = true;
}

int main(int arg, char* argv[])
{
	cv::Mat img = Mat::zeros(Size(32, 32), CV_8UC3);

	Point A(3, 4);
	Point B(20, 30);

	std::string win = "Point flow";
	namedWindow(win);
	Point center(16, 16);
	int radius = 10;
	int count = 4;
	bool onChange = true;
	createTrackbar("O.x", win, &center.x, img.cols-1, on_trackbar, &onChange);
	createTrackbar("O.y", win, &center.y, img.rows-1, on_trackbar, &onChange);
	createTrackbar("Radius", win, &radius, 16, on_trackbar, &onChange);
	createTrackbar("Count", win, &count, 30, on_trackbar, &onChange);

	while (waitKey(30) != 27)
	{
		try
		{
			Mat draw = img.clone();
			auto points = getPointsOnCircle(center, radius, count,draw);

			for (auto i : points)
			{
				DDA(center, i, draw, onChange);
				draw.at<Vec3b>(i) = Vec3b::all(255);
			}

			draw.at<Vec3b>(center) = Vec3b(0, 255, 0);
			Mat scaled;
			cv::resize(draw, scaled, draw.size() * 20,0,0,INTER_NEAREST);
			imshow("Line",scaled);

			if (onChange)
			{
				std::cout << "**********************" << std::endl;
			}
			onChange = false;
		}
		catch (...)
		{
			std::cout << "Circle is out of range" << std::endl;
		}
	}
	return 0;
}