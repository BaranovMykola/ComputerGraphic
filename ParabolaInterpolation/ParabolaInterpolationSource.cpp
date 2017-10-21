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

	circle(draw, A, 6, Scalar(0, 255, 0), -1);
	circle(draw, B, 6, Scalar(0, 255, 0), -1);
	circle(draw, C, 6, Scalar(0, 255, 0), -1);

	Parabola par(A, B, C);

	namedWindow("draw");

	par.draw(draw,0,700);
	imshow("draw", draw);

	waitKey();
}