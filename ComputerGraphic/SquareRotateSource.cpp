#include <iostream>
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include "Square.h"

using namespace std;
using namespace cv;

void main()
{
	const Size imgSize(1000, 1000);
	Mat img = Mat::zeros(imgSize, CV_8UC3);
	int angle = 0;
	Point center(500, 500);
	Point leftup(400, 400);
	Point rightdown(600, 600);
	namedWindow("Image");
	namedWindow("Control");
	createTrackbar("Angle", "Control", &angle, 360);
	createTrackbar("x", "Control", &center.x, imgSize.width);
	createTrackbar("y", "Control", &center.y, imgSize.height);
	createTrackbar("Left Up x", "Control", &leftup.x, imgSize.width);
	createTrackbar("Left Up y", "Control", &leftup.y, imgSize.height);
	createTrackbar("Right down x", "Control", &rightdown.x, imgSize.width);
	createTrackbar("Right down y", "Control", &rightdown.y, imgSize.height);

	while (waitKey(30) != 27)
	{
		Square sq(leftup, Point(leftup.x, rightdown.y), rightdown, Point(rightdown.x, leftup.y));

		Mat kernel = Square::buildRotationMatrix(angle, center);
		auto imgCopy = img.clone();
		circle(imgCopy, center, 5, Scalar::all(255), -1);
		sq.applyKernel(kernel);
		sq.draw(imgCopy);
		imshow("img", imgCopy);
	}
}