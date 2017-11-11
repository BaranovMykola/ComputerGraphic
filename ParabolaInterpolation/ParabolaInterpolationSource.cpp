#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

#include <iostream>

#include "Parabola.h"
#include "Parabola3D.h"

using namespace cv;
using namespace std;

void click(int event, int x, int y, int flags, void *userdata)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		auto vec = static_cast<std::pair<std::vector<cv::Point>*,cv::Mat*>*>(userdata);
		vec->first->emplace_back(x, y);
		Parabola::drawPoints(*vec->second, *vec->first);
		imshow("draw", *vec->second);
	}
}

int main()
{
	Mat draw = Mat::zeros(700, 1600, CV_8UC3);
	namedWindow("Panel");
	int f = 0;
	int t = 0;
	int x = 0;
	int y = 0;
	createTrackbar("F", "Panel", &f, 360);
	createTrackbar("T", "Panel", &t, 360);
	createTrackbar("x", "Panel", &x, 360);
	createTrackbar("y", "Panel", &y, 360);

	std::vector<Point3f> pivot = { Point3f(1,2,3), Point3f(3,5,2), Point3f(4,1,1), Point3f(5,4,1), Point3f(6,3,7), Point3f(8,3,4) };

	auto curve = Parabola3D::interpolate(pivot,draw);
	do
	{
		Mat cl = draw.clone();
		Parabola3D::draw(cl, curve, pivot, f*CV_PI/180, t*CV_PI / 180, x, y);
		imshow("draw", cl);
	}
	while (waitKey(30) != 27);

}