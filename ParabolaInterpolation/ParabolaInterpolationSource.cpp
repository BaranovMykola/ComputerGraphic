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
	
	//Parabola3D p((cv::Mat)( Mat_<float>(3,3) << -7, -48.5, -9, 10, 28.5, 14, 1, 20, 3));
	std::vector<Point3f> pivot = { Point3f(1,2,3), Point3f(3,5,2), Point3f(4,1,1), Point3f(5,4,1), Point3f(6,3,7), Point3f(8,3,4) };
	for (auto i : pivot)
	{
		circle(draw, Point(i.x * 100, i.y * 20), 7, Scalar(0, 0, 255), -1);
	}
	auto curve = Parabola3D::interpolate(pivot,draw);
	Parabola3D::draw(draw, curve);

	imshow("draw", draw);
	waitKey();
}