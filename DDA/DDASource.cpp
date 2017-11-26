#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

#include "DDA.h"

using namespace cv;

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
	createTrackbar("O.x", win, &center.x, img.cols-1);
	createTrackbar("O.y", win, &center.y, img.rows-1);
	createTrackbar("Radius", win, &radius, 16);
	createTrackbar("Count", win, &count, 15);
	

	while (waitKey(30) != 27)
	{
		Mat draw = img.clone();
		auto points = getPointsOnCircle(center, radius, count,draw);
		for (auto i : points)
		{
			DDA(center, i, draw);
			draw.at<Vec3b>(i) = Vec3b::all(255);
		}
		draw.at<Vec3b>(center) = Vec3b(0, 255, 0);
		Mat scaled;
		cv::resize(draw, scaled, draw.size() * 20,0,0,INTER_NEAREST);
		imshow("Line",scaled);
	}
	return 0;
}