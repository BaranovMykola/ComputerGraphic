#include "Parabola3D.h"
#include <opencv2\imgproc.hpp>

#include "MatrixProcessing.h"

using namespace cv;



Parabola3D::Parabola3D(cv::Mat & _data)
{
	cv::Mat data_tp = cv::Mat(_data.cols, _data.rows, CV_32F);
	cv::transpose(_data, data_tp);
	data = data_tp;
}

Parabola3D::Parabola3D(cv::Point3f p1, cv::Point3f p2, cv::Point3f p3)
{
	cv::Mat P = (Mat_<float>(3, 3) << p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z);
	double a = norm(p2 - p1) / (norm(p3 - p2) + norm(p2 - p1));
	alpha = a;
	cv::Mat M = (Mat_<float>(3, 3) << 0, 0, 1, a*a, a, 1, 1, 1, 1);
	cv::Mat Mi;
	invert(M,Mi);
	cv::transpose(Mi*P,data);
}

Parabola3D::~Parabola3D()
{
}

std::vector<cv::Point3f> Parabola3D::plot(double h, double lowerBound, double upperBound)
{
	std::vector<cv::Point3f> points;
	for (double t = lowerBound; t <= upperBound; t+=h)
	{
		points.push_back(Point3f(x(t), y(t), z(t)));
	}
	return points;
}

std::vector<cv::Point3f> Parabola3D::interpolate(std::vector<cv::Point3f> pivot,cv::Mat& img)
{
	std::vector<Point3f> curve;
	double h = 0.1;
	Parabola3D first(pivot[0], pivot[1], pivot[2]);
	auto firstPlot = first.plot(h,-h/2,first.alpha);
	curve.insert(curve.begin(), firstPlot.begin(), firstPlot.end());

	for (int i = 0; i < pivot.size()-3; i++)
	{
		Parabola3D prev(pivot[i], pivot[i + 1], pivot[i + 2]);
		Parabola3D next(pivot[i+1], pivot[i + 2], pivot[i + 3]);
		double a = 0;
		double b = 1;
		for (double t = a; t < b; t+=h)
		{
			double off = prev.alpha - t;
			double max = b-a;
			curve.push_back(prev.take((1-prev.alpha)*t+prev.alpha)*(b-t) / max + next.take(next.alpha*t)*(t- a)/max);
			//cv::circle(img, Point(curve.back().x * 100, curve.back().y * 20), 3, Scalar::all(255), 1);
		}
		//prev.draw(img);
		//next.draw(img);
	}

	Parabola3D last(pivot[pivot.size()-3], pivot[pivot.size()-2], pivot[pivot.size()-1]);
	auto lastPlot = last.plot(h,last.alpha,1+h/2);
	curve.insert(curve.end(), lastPlot.begin(), lastPlot.end());
	return curve;
}

void Parabola3D::draw(cv::Mat & img, std::vector<cv::Point3f> curve, std::vector<cv::Point3f> pivot, double f, double t, std::vector<int> move, double scale)
{
	cv::Mat moveKern = (cv::Mat_<float>(4, 4) << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, move[0], move[1], move[2], 1);

	cv::Mat _kern = (cv::Mat_<float>(4, 4) << cos(f), sin(f)*sin(t), -sin(f)*cos(t), 0,
					0, cos(t), sin(t), 0,
					sin(f), -cos(f)*sin(t), cos(f)*cos(t), 0,
					0,0,0,scale);
	Mat kern = _kern* moveKern;
	

	std::vector<Point3f> pivotModified = applyKern(pivot, kern);

	std::vector<Point3f> curveModified = applyKern(curve, kern);

	for (auto i : pivotModified)
	{
		cv::circle(img, Point(i.x, i.y), 5, Scalar(0,0,255), -1);
	}

	for (int i = 0; i < curveModified.size() - 1; i++)
	{
		line(img, Point(curveModified[i].x, curveModified[i].y), Point(curveModified[i + 1].x, curveModified[i + 1].y), Scalar::all(255), 1);
	}

}

cv::Point3f Parabola3D::take(double t)
{
	return cv::Point3f(x(t),y(t),z(t));
}

double Parabola3D::x(double t)
{
	float* row = data.ptr<float>(0);
	return row[0] * t*t + row[1] * t + row[2] ;
}

double Parabola3D::y(double t)
{
	float* row = data.ptr<float>(1);
	return row[0] * t*t + row[1] * t + row[2];
}

double Parabola3D::z(double t)
{
	float* row = data.ptr<float>(2);
	return row[0] * t*t + row[1] * t + row[2];
}


