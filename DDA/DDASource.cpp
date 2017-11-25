#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>

#include "DDA.h"

using namespace cv;

int main(int arg, char* argv[])
{
	cv::Mat img = Mat::zeros(Size(700, 700), CV_8UC3);

	Point A(100, 100);
	Point B(500, 200);

	std::string win = "Point flow";
	namedWindow(win);
	createTrackbar("A.x", win, &A.x, 700);
	createTrackbar("A.y", win, &A.y, 700);
	createTrackbar("B.x", win, &B.x, 700);
	createTrackbar("B.y", win, &B.y, 700);
	
	while (waitKey(30) != 27)
	{
		Mat draw = img.clone();
		DDA(B, A, draw);
		imshow("Line",draw);
	}
	return 0;
}