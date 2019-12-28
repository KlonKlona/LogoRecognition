#pragma once
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class MorphologicalProcess
{
public:
	void erosion(cv::Mat& inputImage, cv::Mat& outputImage);
	void dilation(cv::Mat& inputImage, cv::Mat& outputImage);
	void plotHistogram(cv::Mat& inputImage);
};
