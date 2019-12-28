#include "UnsharpMask.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <corecrt_math_defines.h>
#include <iostream>
#include <algorithm>


void UnsharpMask::showKernel() {
	for (int i = 0; i < (this->matrix_size); ++i) {
		for (int j = 0; j < (this->matrix_size); ++j) {
			std::cout << this->kernel[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

void UnsharpMask::KernelCreation(double _sigma) {
	double sigma = _sigma;
	double r = 0;
	double s = 2.0 * sigma * sigma;
	double sum = 0.0;

	for (int i = -(this->matrix_size) / 2; i <= (this->matrix_size) / 2; ++i) {
		for (int j = -(this->matrix_size) / 2; j <= (this->matrix_size) / 2; ++j) {
			r = sqrt(i * i + j * j);
			this->kernel[i + ((this->matrix_size) / 2)][j + ((this->matrix_size) / 2)] 
				= (exp(-(r * r) / s)) / (M_PI * s);
			sum += this->kernel[i + 2][j + 2];
		}
	}

	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			this->kernel[i][j] /= sum;

	return;
}

void UnsharpMask::GaussianBlur(cv::Mat& inputImage, cv::Mat& outputImage) {
	CV_Assert(inputImage.depth() != sizeof(uchar));
	CV_Assert(outputImage.depth() != sizeof(uchar));
	cv::Mat_<cv::Vec3b> _I = inputImage;
	cv::Mat_<cv::Vec3b> _O = outputImage;
	double sum = 0;
	for (int i = (this->matrix_size) / 2; i < _I.rows - (this->matrix_size) / 2; ++i) {
		for (int j = (this->matrix_size) / 2; j < _I.cols - (this->matrix_size) / 2; ++j) {
			for (int c = 0; c < _I.channels(); ++c) {
				_O.at<cv::Vec3b>(i, j)[c] = 0;
				sum = 0;
				for (int k = -(this->matrix_size) / 2; k <= (this->matrix_size) / 2; ++k) {
					for (int l = -(this->matrix_size) / 2; l <= (this->matrix_size) / 2; ++l) {
						sum += (_I.at<cv::Vec3b>(i + k, j + l)[c])
							* this->kernel[k + (this->matrix_size) / 2][l + (this->matrix_size) / 2];
					}
				}
				_O.at<cv::Vec3b>(i, j)[c] = cv::saturate_cast<uchar> (sum);
			}
		}
	}
	outputImage = _O;
	return;
}


void UnsharpMask::UnscharpMask(cv::Mat& inputImage, cv::Mat& outputImage, cv::Mat& blurredImage)
{
	CV_Assert(inputImage.depth() != sizeof(uchar));
	CV_Assert(outputImage.depth() != sizeof(uchar));
	cv::Mat_<cv::Vec3b> _I = inputImage;
	cv::Mat_<cv::Vec3b> _O = outputImage;
	cv::Mat_<cv::Vec3b> _B = blurredImage;

	for (int i = 2; i < _I.rows - this->matrix_size + 1; ++i) {
		for (int j = 2; j < _I.cols - this->matrix_size + 1; ++j) {
			for (int c = 0; c < _I.channels(); ++c) {
				_O.at<cv::Vec3b>(i, j)[c] = std::max(0, std::min(2 * _I.at<cv::Vec3b>(i, j)[c]
					- _B.at<cv::Vec3b>(i, j)[c], 255));
			}
		}
	}
	outputImage = _O;
	return;
}