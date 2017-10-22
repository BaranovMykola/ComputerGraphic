#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

#include <iostream>

#include "Parabola.h"

using namespace cv;
using namespace std;

int main()
{
	Mat draw = Mat::zeros(700, 1600, CV_8UC3);
	Point A(200, 200);
	Point B(300, 500);
	Point C(600, 600);
	Point D(1000, 600);
	Point E(1500, 100);

	std::vector<Point> points{ A,B,C,D,E };

	namedWindow("Delay");
	Parabola::delay = 1;
	createTrackbar("Delay", "Delay", &Parabola::delay, 20);
	RNG rnd(10);
	Parabola::drawPoints(draw, points);
	Parabola::interpolate(draw, points);
	imshow("draw", draw);

	waitKey();
}