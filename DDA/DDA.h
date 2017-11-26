#pragma once
#include <opencv2\core.hpp>

#include <vector>

void DDA(cv::Point2f A, cv::Point2f B, cv::Mat& img, bool = false);

std::vector<cv::Point> getPointsOnCircle(cv::Point center, int r, int n, cv::Mat& img = cv::Mat());