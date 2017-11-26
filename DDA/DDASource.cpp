#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

#include "DDA.h"

using namespace cv;

int main(int arg, char* argv[])
{
	cv::Mat img = Mat::zeros(Size(32, 32), CV_8UC3);

	Point A(3, 4);
	Point B(20, 30);

	std::string win = "Point flow";
	namedWindow(win);
	createTrackbar("A.x", win, &A.x, img.cols-1);
	createTrackbar("A.y", win, &A.y, img.rows-1);
	createTrackbar("B.x", win, &B.x, img.cols-1);
	createTrackbar("B.y", win, &B.y, img.rows-1);
	
	while (waitKey(30) != 27)
	{
		Mat draw = img.clone();
		DDA(B, A, draw);
		Mat scaled;
		cv::resize(draw, scaled, draw.size() * 20,0,0,INTER_NEAREST);
		imshow("Line",scaled);
	}
	return 0;
}