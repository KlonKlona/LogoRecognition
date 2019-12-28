#pragma once
#include <opencv2\core\base.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <queue>
#include <list>
#include "Segment.h"

#define CV_BGR2HLS cv::COLOR_BGR2HLS

class LakersLogoRecognizer
{
public:
	std::list <Segment> segments;

	LakersLogoRecognizer(cv::Mat& image) : oldImage(image) {
		newImage = cv::Mat(image.size(), CV_8UC3);
	}

	void recognize();

private:
	cv::Mat oldImage;
	cv::Mat newImage;
	static const cv::Scalar MIN_PURPLE_HLS;
	static const cv::Scalar MAX_PURPLE_HLS;
	static const int RANDOM_SEED;


	void performSegmentation();
	void performAnalysis();
	void performRecognition();
	cv::Mat thresholding(const cv::Mat&);
	bool isPurple(int h, int l, int s);
	void floodFill(int row, int col, cv::Scalar color);
	cv::Scalar randomColor(cv::RNG& rng);
	void deleteSmall();
	bool isLAKEWord(const Segment&);
	bool isRLetter(const Segment&);
	bool isSLetter(const Segment&);
	bool isWord(const Segment&);
};

