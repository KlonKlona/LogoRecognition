#pragma once
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <list>

class Segment {
public:
	Segment(cv::Scalar _color = cv::Scalar(255, 255, 255)) : color(_color), surface(0), circumference(0),
		m01(0), m10(0), m02(0), m20(0), m03(0), m30(0), m11(0), m21(0), m12(0),
		M01(0), M10(0), M02(0), M20(0), M03(0), M30(0), M11(0), M21(0), M12(0),
		NM1(0), NM2(0), NM3(0), NM7(0), center_i(0), center_j(0) {}

	cv::Scalar color;
	std::list <cv::Point2i> points;

	bool operator==(const Segment& q);
	void analyseSegment();
	double calc_mpq(int p, int q);

private:
	double surface;
	double circumference;
	double m01;
	double m10;
	double m02;
	double m20;
	double m03;
	double m30;
	double m11;
	double m21;
	double m12;

	double center_i;
	double center_j;

	double M01;
	double M10;
	double M02;
	double M20;
	double M03;
	double M30;
	double M11;
	double M21;
	double M12;

	double NM1;
	double NM2;
	double NM3;
	double NM7;
};

