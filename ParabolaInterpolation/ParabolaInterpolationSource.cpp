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
	std::vector<Point> points{};

	namedWindow("draw");
	setMouseCallback("draw", click, &make_pair(&points,&draw));
	imshow("draw", draw);
	waitKey();

	Parabola::interpolate(draw, points,100);

	imshow("draw", draw);
	waitKey();
}