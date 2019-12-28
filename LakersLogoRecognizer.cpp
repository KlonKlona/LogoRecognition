#include "LakersLogoRecognizer.h"

const cv::Scalar LakersLogoRecognizer::MIN_PURPLE_HLS = cv::Scalar(120, 20, 10);
const cv::Scalar LakersLogoRecognizer::MAX_PURPLE_HLS = cv::Scalar(255, 170, 160);
const int LakersLogoRecognizer::RANDOM_SEED = 0;

void LakersLogoRecognizer::recognize() {
	cv::Mat hlsImage;
	cvtColor(this->oldImage, hlsImage, CV_BGR2HLS);
	this->newImage = thresholding(hlsImage);

	performSegmentation();
	performAnalysis();
	performRecognition();

	cv::namedWindow("framed");
	imshow("framed", this->oldImage);
	cv::namedWindow("colored");
	imshow("colored", this->newImage);
}

void LakersLogoRecognizer::floodFill(int row, int col, cv::Scalar color) {
	std::list <cv::Point2i> pointQueue;
	pointQueue.push_back(cv::Point2i(col, row));
	cv::Point2i current, left, right, top, bottom, leftTop, leftBottom, rightTop, rightBottom;

	while (!pointQueue.empty()) {
		current = pointQueue.front();
		pointQueue.pop_front();

		this->newImage.at<cv::Vec3b>(current)[0] = (uchar)color[0];
		this->newImage.at<cv::Vec3b>(current)[1] = (uchar)color[1];
		this->newImage.at<cv::Vec3b>(current)[2] = (uchar)color[2];

		segments.back().points.push_back(current);

		left = cv::Vec2i(current.x - 1, current.y);
		right = cv::Vec2i(current.x + 1, current.y);
		top = cv::Vec2i(current.x, current.y - 1);
		bottom = cv::Vec2i(current.x, current.y + 1);
		leftTop = cv::Vec2i(current.x - 1, current.y - 1);
		leftBottom = cv::Vec2i(current.x - 1, current.y + 1);
		rightTop = cv::Vec2i(current.x + 1, current.y - 1);
		rightBottom = cv::Vec2i(current.x + 1, current.y + 1);

		if (left.x >= 0 && newImage.at<cv::Vec3b>(left)[0] == 255 && newImage.at<cv::Vec3b>(left)[1] == 255 &&
			newImage.at<cv::Vec3b>(left)[2] == 255 && find(pointQueue.begin(), pointQueue.end(), left) == pointQueue.end()) {
			pointQueue.push_back(left);
		}
		if (right.x < newImage.cols && newImage.at<cv::Vec3b>(right)[0] == 255 && newImage.at<cv::Vec3b>(right)[1] == 255 &&
			newImage.at<cv::Vec3b>(right)[2] == 255 && find(pointQueue.begin(), pointQueue.end(), right) == pointQueue.end()) {
			pointQueue.push_back(right);
		}
		if (top.y >= 0 && newImage.at<cv::Vec3b>(top)[0] == 255 && newImage.at<cv::Vec3b>(top)[1] == 255 &&
			newImage.at<cv::Vec3b>(top)[2] == 255 && find(pointQueue.begin(), pointQueue.end(), top) == pointQueue.end()) {
			pointQueue.push_back(top);
		}
		if (bottom.y < newImage.rows && newImage.at<cv::Vec3b>(bottom)[0] == 255 && newImage.at<cv::Vec3b>(bottom)[1] == 255
			&& newImage.at<cv::Vec3b>(bottom)[2] == 255 && find(pointQueue.begin(), pointQueue.end(), bottom) == pointQueue.end()) {
			pointQueue.push_back(bottom);
		}
		if (leftTop.x >= 0 && leftTop.y >= 0 && newImage.at<cv::Vec3b>(left)[0] == 255 && newImage.at<cv::Vec3b>(left)[1] == 255 &&
			newImage.at<cv::Vec3b>(left)[2] == 255 && find(pointQueue.begin(), pointQueue.end(), leftTop) == pointQueue.end()) {
			pointQueue.push_back(leftTop);
		}
		if (leftBottom.x >= 0 && leftBottom.y < newImage.rows && newImage.at<cv::Vec3b>(left)[0] == 255 &&
			newImage.at<cv::Vec3b>(left)[1] == 255 && newImage.at<cv::Vec3b>(left)[2] == 255 &&
			find(pointQueue.begin(), pointQueue.end(), leftBottom) == pointQueue.end()) {
			pointQueue.push_back(leftBottom);
		}
		if (rightTop.x < newImage.cols && rightTop.y >= 0 && newImage.at<cv::Vec3b>(right)[0] == 255 && 
			newImage.at<cv::Vec3b>(right)[1] == 255 && newImage.at<cv::Vec3b>(right)[2] == 255 &&
			find(pointQueue.begin(), pointQueue.end(), rightTop) == pointQueue.end()) {
			pointQueue.push_back(rightTop);
		}
		if (rightBottom.x < newImage.cols && rightBottom.y < newImage.rows && newImage.at<cv::Vec3b>(right)[0] == 255 &&
			newImage.at<cv::Vec3b>(right)[1] == 255 && newImage.at<cv::Vec3b>(right)[2] == 255 &&
			find(pointQueue.begin(), pointQueue.end(), rightBottom) == pointQueue.end()) {
			pointQueue.push_back(rightBottom);
		}
	}
}

void LakersLogoRecognizer::deleteSmall() {
	std::list<Segment>::iterator it;
	for (it = segments.begin(); it != segments.end(); ++it) {

	}
}

bool LakersLogoRecognizer::isLAKEWord(const Segment&)
{
	return false;
}

bool LakersLogoRecognizer::isRLetter(const Segment&)
{
	return false;
}

bool LakersLogoRecognizer::isSLetter(const Segment&)
{
	return false;
}

bool LakersLogoRecognizer::isWord(const Segment&)
{
	return false;
}

void LakersLogoRecognizer::performSegmentation() {
	cv::Scalar color;
	cv::RNG rng(RANDOM_SEED);
	for (int i = 0; i < this->newImage.rows; ++i) {
		for (int j = 0; j < this->newImage.cols; ++j) {
			if (newImage.at<cv::Vec3b>(i, j)[0] == 255 && newImage.at<cv::Vec3b>(i, j)[1] == 255 && newImage.at<cv::Vec3b>(i, j)[2] == 255) {
				color = randomColor(rng);
				segments.push_back(Segment(color));
				floodFill(i, j, color);
			}
		}
	}
	deleteSmall();
}

void LakersLogoRecognizer::performAnalysis()
{
}

void LakersLogoRecognizer::performRecognition()
{
}

cv::Mat LakersLogoRecognizer::thresholding(const cv::Mat& I) {
	CV_Assert(I.depth() != sizeof(uchar));
	double S = 0;
	cv::Mat first(I.rows, I.cols, CV_8UC3);
	cv::Mat_<cv::Vec3b> _I = I;
	cv::Mat_<cv::Vec3b> _R = first;

	for (int i = 0; i < _I.rows; ++i) {
		for (int j = 0; j < _I.cols; ++j) {
			if (isPurple(_I.at<cv::Vec3b>(i, j)[0], _I.at<cv::Vec3b>(i, j)[1], _I.at<cv::Vec3b>(i, j)[2])) {
				_R.at<cv::Vec3b>(i, j)[0] = 255;
				_R.at<cv::Vec3b>(i, j)[1] = 255;
				_R.at<cv::Vec3b>(i, j)[2] = 255;
			}
			else {
				_R.at<cv::Vec3b>(i, j)[0] = 0;
				_R.at<cv::Vec3b>(i, j)[1] = 0;
				_R.at<cv::Vec3b>(i, j)[2] = 0;
			}
		}
	}

	return _R;
}

bool LakersLogoRecognizer::isPurple(int h, int l, int s) {
	if ((h <= MAX_PURPLE_HLS[0] && h >= MIN_PURPLE_HLS[0]) 
		&& (l <= MAX_PURPLE_HLS[1] && l >= MIN_PURPLE_HLS[1])
		&& (s <= MAX_PURPLE_HLS[2] && s >= MIN_PURPLE_HLS[2]))
		return true;
	else
		return false;
}

cv::Scalar LakersLogoRecognizer::randomColor(cv::RNG& rng) {
	rng.next();
	int color = (unsigned)rng;
	return cv::Scalar(color % 256, (2*color) % 256, (3*color) % 256);
}

//warunki dla koloru fioletowego w przestrzeni RGB
//if ((_I.at<cv::Vec3b>(i, j)[0] > 30) && (_I.at<cv::Vec3b>(i, j)[0] < 130) &&
//	(_I.at<cv::Vec3b>(i, j)[1] > 0) && (_I.at<cv::Vec3b>(i, j)[1] < 80) &&
//	(_I.at<cv::Vec3b>(i, j)[2] > 10) && (_I.at<cv::Vec3b>(i, j)[2] < 110)) {
