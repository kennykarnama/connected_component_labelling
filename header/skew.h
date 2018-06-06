#ifndef SKEW_H
#define SKEW_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <cmath>
#include "projection.h"

class Skew
{
public:
	Skew();
	~Skew();
	
	std::vector<double> entropy(std::vector<double>);

	std::vector<double> entropy(std::vector<int>,int,int);

	std::vector<double> Eh(std::vector<double>);

	double E(std::vector<double>);

	std::vector<double> deskew(int,int,cv::Mat);

	std::vector<double> deskew(double,double,cv::Mat);

	int potential_angle(int,int,std::vector<double>);



	
};

#endif

