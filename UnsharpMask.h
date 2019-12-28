#pragma once
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class UnsharpMask {
public:
	UnsharpMask(int _matrix_size) {
		this->matrix_size = _matrix_size;
		kernel = new double* [_matrix_size];
		for (int i = 0; i < _matrix_size; ++i)
			kernel[i] = new double[_matrix_size];
	}

	void showKernel();
	void KernelCreation(double sigman);
	void GaussianBlur(cv::Mat& inputImage, cv::Mat& outputImage);
	void UnscharpMask(cv::Mat& inputImage, cv::Mat& outputImage, cv::Mat& blurredImage);
private:
	double** kernel;
	int matrix_size;
};

