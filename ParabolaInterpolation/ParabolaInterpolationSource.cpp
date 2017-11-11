#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

#include <iostream>
#include <iterator>

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
	namedWindow("Projection", CV_WINDOW_NORMAL);
	int oxRotatetion = 0;
	int oyRotation = 0;
	int scale = 0;
	std::vector<int> move(3);
	createTrackbar("OY", "Projection", &oxRotatetion, 360);
	createTrackbar("OX", "Projection", &oyRotation, 360);
	createTrackbar("X", "Projection", &move[0], draw.cols);
	createTrackbar("Y", "Projection", &move[1], draw.rows);
	createTrackbar("Z", "Projection", &move[2], 360);
	createTrackbar("Scale", "Projection", &scale, 100);

	std::vector<Point3f> pivot = { Point3f(1,2,3), Point3f(3,5,2), Point3f(4,1,1), Point3f(5,4,1), Point3f(6,3,7), Point3f(8,3,4) };

	auto curve = Parabola3D::interpolate(pivot,draw);
	do
	{
		Mat cl = draw.clone();
		Parabola3D::draw(cl, curve, pivot, oxRotatetion*CV_PI/180, oyRotation*CV_PI / 180, move, 1/(scale+1.0));
		imshow("draw", cl);
	}
	while (waitKey(30) != 27);

}