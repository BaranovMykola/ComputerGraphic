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

	Point A(400, 400);
	Point B(300, 300);
	Point C(300, 400);
	namedWindow("Image");
	namedWindow("Control Panel", CV_WINDOW_FREERATIO);
	createTrackbar("Angle", "Control Panel", &angle, 360);
	createTrackbar("x", "Control Panel", &center.x, imgSize.width);
	createTrackbar("y", "Control Panel", &center.y, imgSize.height);
	createTrackbar("Left Up x", "Control Panel", &leftup.x, imgSize.width);
	createTrackbar("Left Up y", "Control Panel", &leftup.y, imgSize.height);
	createTrackbar("Right down x", "Control Panel", &rightdown.x, imgSize.width);
	createTrackbar("Right down y", "Control Panel", &rightdown.y, imgSize.height);

	createTrackbar("A.x", "Control Panel", &A.x, imgSize.width);
	createTrackbar("A.y", "Control Panel", &A.y, imgSize.height);
	createTrackbar("B.x", "Control Panel", &B.x, imgSize.width);
	createTrackbar("B.y", "Control Panel", &B.y, imgSize.height);
	createTrackbar("C.x", "Control Panel", &C.x, imgSize.width);
	createTrackbar("C.y", "Control Panel", &C.y, imgSize.height);

	while (waitKey(30) != 27)
	{
		Shape sq({leftup, Point(leftup.x, rightdown.y), rightdown, Point(rightdown.x, leftup.y)});
		Shape tr({ A,B,C });

		Mat kernel = Shape::buildRotationMatrix(angle, center);
		auto imgCopy = img.clone();
		circle(imgCopy, center, 5, Scalar::all(255), -1);
		sq.applyKernel(kernel);
		tr.applyKernel(kernel);
		tr.draw(imgCopy);
		sq.draw(imgCopy);
		imshow("Image", imgCopy);
	}
}