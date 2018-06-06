#ifndef CCL_H
#define CCL_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdlib>
#include "union.h"

	class CCL
	{
	public:
		CCL();
		~CCL();

		cv::Mat connectedComponentLabelling(cv::Mat);

		cv::Mat visualize(cv::Mat);

		std::vector<ushort> getComponentLabels(cv::Mat);

		std::map<ushort,std::vector<cv::Point> > getComponentPoints(std::vector<ushort>,cv::Mat);

		std::vector<cv::RotatedRect> getRotatedRect(std::map<ushort, std::vector<cv::Point> >);

		std::vector<cv::Rect> getRect(std::vector<cv::RotatedRect>);

		std::vector<cv::Point> getComponentPoints(cv::Mat);

		cv::RotatedRect getRotatedRect(std::vector<cv::Point>);

		std::vector< std::vector<cv::Point> > getConvexHulls(std::map<ushort, std::vector<cv::Point> >);

		cv::Mat visualizeRect(std::vector<cv::Rect>, cv::Mat);

		cv::Mat visualizeRect(cv::Rect, cv::Mat);

		cv::Mat visualizeRotatedRect(cv::RotatedRect,cv::Mat);

		cv::Mat filter(std::map<ushort,std::vector<cv::Point> >, double, cv::Mat);

		void sortRotatedRectangles(std::vector<cv::Rect>&);

		struct less_than_key
		{
		    inline bool operator() (const cv::Rect& r1, const cv::Rect& r2)
		    {

		    	// cv::Point p1 = r1.br();

		    	// cv::Point p2 = r2.br();

		        return (r1.x < r2.x);
		    }
		};	
		
		/* data */

	
		
	
	};
#endif
