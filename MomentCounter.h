#pragma once
#include <opencv2\core\base.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

class MomentCounter
{
public:
	double M1_moment(cv::Mat& I);
	double M3_moment(cv::Mat& I);
	double M7_moment(cv::Mat& I);
};

