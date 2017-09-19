#include <iostream>
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include "Square.h"

using namespace std;
using namespace cv;

void main()
{
	Mat img = Mat::zeros(Size(1000, 1000), CV_8UC3);
	//circle(img, Point(500, 500), 300, Scalar(0, 0, 255), 15);
		int l = 1;
		int x = 0;
		int y = 0;
		namedWindow("img");
		createTrackbar("angle", "img", &l, 360);
		createTrackbar("x", "img", &x, 400);
		createTrackbar("y", "img", &y, 400);

	while (waitKey(30) != 27)
	{
		Point center(x, y);
		float r = (CV_PI/180.0) * (l);
		//r = l;
		Square sq(Point(300, 300), Point(300, 500), Point(500, 500), Point(500, 300));

		/*Mat l2 = (Mat_<float>(3, 3) << 1, 0, 0,
				  0, 1, 0,
				  -x, -y, 1);

		Mat kern = (Mat_<float>(3, 3) << cos(r), sin(r),0,
					-sin(r), cos(r), 0,
					0,0, 1);

		Mat r2 = (Mat_<float>(3, 3) << 1,0, 0,
					0,1, 0,
					x, y, 1);

		Mat k = l2*kern*r2;*/
		Mat k = sq.buildRotationMatrix(r, Point(x, y));

		auto i = img.clone();
		circle(i, center, 5, Scalar::all(255), -1);
		//sq.move(-x,-y);
		sq.applyKernel(k);
		//sq.move(x,y);
		sq.draw(i);
		imshow("img", i);
	}
	waitKey();
}