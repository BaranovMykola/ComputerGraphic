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
	Parabola3D p(Point3f(1, 20, 3), Point3f(2.25, 23, 4.75), Point3f(4, 0, 8));
	p.draw(draw);

	imshow("draw", draw);
	waitKey();
}