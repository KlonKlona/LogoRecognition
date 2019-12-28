#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "UnsharpMask.h"
#include "MorphologicalProcess.h"
#include "LakersLogoRecognizer.h"
#include <iostream>
#include <vector>
#include "main.h"

/// Global variables
cv::Mat src, erosion_dst, dilation_dst;

int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 1;
int const max_elem = 2;
int const max_kernel_size = 21;



int main(int, char* []) {
	std::cout << "Start ..." << std::endl;
	cv::Mat image = cv::imread("C:/Users/rosja/source/repos/LogoRecognition/lakers2Small.png");
	cv::Mat blurred = image.clone();
	cv::Mat result = image.clone();
	cv::Mat binarized;
	cv::Mat dilated;
	
	UnsharpMask mask = UnsharpMask(5);
	MorphologicalProcess Morpho;
	mask.KernelCreation(1);
	mask.GaussianBlur(image, blurred);
	mask.UnscharpMask(image, result, blurred);
	//binarized = binarize(result);
	//Morpho.dilation(binarized, dilated);
	//Morpho.plotHistogram(result);
	//cv::imshow("LeBron", image);
	LakersLogoRecognizer llg = LakersLogoRecognizer(result);
	llg.recognize();
	//cv::imshow("UnsharpedLebron", result);
	//cv::imshow("Binarized", binarized);
	//cv::imshow("Dilation Demo", dilated);
	cv::waitKey(-1);
	return 0;
}