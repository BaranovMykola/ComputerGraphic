#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

#include <iostream>

#include "Parabola.h"

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
	Point A(200, 200);
	Point B(300, 500);
	Point C(600, 600);
	Point D(1000, 600);
	Point E(1500, 100);

	std::vector<Point> points{ A,B,C,D,E };

	namedWindow("draw");
	setMouseCallback("draw", click, &make_pair(&points,&draw));
	imshow("draw", draw);
	waitKey();
	RNG rnd(10);
	Parabola::drawPoints(draw, points);
	Parabola::interpolate(draw, points,300);
	imshow("draw", draw);

	waitKey();
}