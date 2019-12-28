#include "MomentCounter.h"

double MomentCounter::M1_moment(cv::Mat& I)
{
	CV_Assert(I.depth() != sizeof(uchar));
	double m00 = 0;
	double m10 = 0;
	double m01 = 0;
	double m20 = 0;
	double m02 = 0;
	double M20 = 0;
	double M02 = 0;
	double M1 = 0;

	cv::Mat first(I.rows, I.cols, CV_8UC3);
	cv::Mat_<cv::Vec3b> _I = I;
	cv::Mat_<cv::Vec3b> _R = first;
	for (int i = 0; i < _I.rows; ++i) {
		for (int j = 0; j < _I.cols; ++j) {
			if ((_I.at<cv::Vec3b>(i, j)[0] == 0) && (_I.at<cv::Vec3b>(i, j)[1] == 0) && (_I.at<cv::Vec3b>(i, j)[2] == 0)) {
				m00++;
				m10 += i * 1;
				m01 += j * 1;
				m20 += pow(i, 2) * 1;
				m02 += pow(j, 2) * 1;
			}
		}
	}
	M02 = m02 - ((m01 * m01) / m00);
	M20 = m20 - ((m10 * m10) / m00);
	M1 = (M20 + M02) / (m00 * m00);
	return M1;
}

double MomentCounter::M3_moment(cv::Mat& I)
{
	return 0.0;
}

double MomentCounter::M7_moment(cv::Mat& I)
{
	return 0.0;
}
