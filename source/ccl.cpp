#include "ccl.h"



CCL::CCL(){

}

CCL::~CCL(){

}

cv::Mat CCL::connectedComponentLabelling(cv::Mat img){

	Union u;

	std::vector<ushort> labels;

	// labels initialize with 0 

	labels.push_back(0);



	cv::Mat hasil (img.rows,img.cols,CV_16UC1,cv::Scalar(0));

	std::vector<ushort> jawaban;

	jawaban = labels;



	// first pass

	// iterate over matrix

	for (int y = 0; y < img.rows; ++y)
	{
		/* code */
		for (int x = 0; x < img.cols; ++x)
		{
			/* code */

			// if it is foreground pixel

			if(img.at<uchar>(y,x) == 0){


				int pY = y;

				int pX = x;

				int isExistLeft = 0;

				int isExistTop = 0;



					// check if exist left and top from current pixel

				if((pX - 1) > -1 && img.at<uchar>(pY,pX-1) == 0){
					isExistLeft = 1;
				}

				if((pY - 1) > -1 && img.at<uchar>(pY-1,pX) == 0){
					isExistTop = 1;
				}

				//cout << isExistLeft <<" " << isExistTop << " "<<(int)img.at<uchar>(y,x) << endl;

				// if not exist at all, make new label on current pixel

				ushort currentLabel = 0;

				if((isExistLeft == 0) && isExistTop == 0){

					currentLabel = labels.at(labels.size()-(ushort)1)+(ushort)1;

					//cout << "currentLabel " << (int)currentLabel << endl;

					

				}

				// if left pixel exist, but not top pixel

				else if((isExistLeft == 1) && (isExistTop == 0)){
					// copy label from left pixel
					currentLabel = hasil.at<ushort>(pY,pX-1);



				}

				// if top pixel exists, but not left pixel

				else if((isExistLeft == 0) && (isExistTop == 1)){
					currentLabel = hasil.at<ushort>(pY-1,pX);
				}

				// exist both of them

				else{

					ushort leftLabel = hasil.at<ushort>(pY,pX-1);

					ushort topLabel = hasil.at<ushort>(pY-1,pX);

					if(leftLabel < topLabel ){
						
						currentLabel = leftLabel;

						// union operation 

						u.unionOperation(jawaban,topLabel,leftLabel);

					}

					else {
						currentLabel = topLabel;

						u.unionOperation(jawaban,leftLabel,topLabel);
					}

					

				}

				hasil.at<ushort>(pY,pX) = currentLabel;

				int isExist = 0;

				for (int i = 0; i < labels.size(); ++i)
				{
					/* code */
					if(labels.at(i) == currentLabel ){
						isExist = 1;
						break;
					}
				}

				if(isExist == 0){
					labels.push_back(currentLabel);

					jawaban.push_back(currentLabel);
					
				}

				

			}

		

			

		}
	}

	

	// second pass

	for (int y = 0; y < hasil.rows; ++y)
	{
		/* code */
		for (int x = 0; x < hasil.cols; ++x)
		{
			  
			int indeks = (int)hasil.at<ushort>(y,x);

			

			hasil.at<ushort>(y,x) = jawaban.at(indeks);
		}
	}

	

	return hasil;


}

cv::Mat CCL::visualize(cv::Mat hasil){

	cv::RNG rng(12345);

	 std::vector<ushort> labels;

	 for (int i = 0; i < hasil.rows; ++i)
	 {
	 	/* code */
	 	for (int j = 0; j < hasil.cols; ++j)
	 	{
	 		/* code */
	 		ushort p = hasil.at<ushort>(i,j);

	 		//cout << "scan pixel "<< (int)p<< endl;

	 		int isExist = 0;

	 		for (int c = 0; c < labels.size(); ++c)
	 		{
	 			/* code */
	 			if(labels.at(c) == p){

	 				isExist = 1;
	 				break;
	 			}
	 		}

	 		if(isExist == 0){
	 			labels.push_back(p);
	 		}
	 	}
	 }

	 // color each label using random colors

	 std::map<ushort,cv::Vec3b> warna_cc;

	 warna_cc.insert(std::pair<ushort,cv::Vec3b> (0,cv::Vec3b(255, 255, 255)));


	
	 for (int i = 0; i < labels.size(); ++i)
	 {
	 	/* code */



	 	warna_cc.insert(std::pair<ushort,cv::Vec3b> (labels.at(i),cv::Vec3b( (rand()%255), (rand()%255), (rand()%255) )));

	 	// cout << warna_cc[labels.at(i)] << endl;
	 	 //cout <<  "label "<<(int)labels.at(i)<< " " ;
	 }

	// make visual representation of image

	  cv::Mat cc_img(hasil.size(), CV_8UC3);

	  for (int i = 0; i < cc_img.rows; ++i)
	  {
	  	/* code */
	  	for (int j = 0; j < cc_img.cols; ++j)
	  	{
	  		/* code */
	  		ushort p = hasil.at<ushort>(i,j);

	  		cv::Vec3b &pixel = cc_img.at<cv::Vec3b>(i, j);

	  		

	  		pixel = warna_cc[p];
	  		//pixel = cv::Vec3b( 0, 0, 0 );
	  	}
	  }

	  return cc_img;
}

std::vector<ushort> CCL::getComponentLabels(cv::Mat hasil){
	 
	 std::vector<ushort> labels;

	 for (int i = 0; i < hasil.rows; ++i)
	 {
	 	/* code */
	 	for (int j = 0; j < hasil.cols; ++j)
	 	{
	 		/* code */
	 		ushort p = hasil.at<ushort>(i,j);

	 		//cout << "scan pixel "<< (int)p<< endl;

	 		int isExist = 0;

	 		for (int c = 0; c < labels.size(); ++c)
	 		{
	 			/* code */
	 			if(labels.at(c) == p){

	 				isExist = 1;
	 				break;
	 			}
	 		}

	 		if(isExist == 0){
	 			labels.push_back(p);
	 		}
	 	}
	 }

	 return labels;
}

std::map<ushort,std::vector<cv::Point> > CCL::getComponentPoints(std::vector<ushort> labels,cv::Mat cc){
	
	std::map<ushort, std::vector<cv::Point> > m;

	

	std::vector< std::vector<cv::Point> > wew;

	std::map<int, std::vector<cv::Point> > m2;

	for (int i = 0; i < labels.size(); ++i)
	{
		/* code */
		// cari di mat

		ushort label = labels.at(i);

			

		// exclude background pixel

		if(label!=0){

			std::vector<cv::Point> points;
			

		for (int row = 0; row < cc.rows; ++row)
		{
			/* code */
			for (int col = 0; col < cc.cols; ++col)
			{
				/* code */
				ushort p = cc.at<ushort>(row,col);

				if(p == label){

					

					cv::Point p;
					
					p.x = col;
					
					p.y = row;

					points.push_back(p);



				}
			}
		}

	

		std::vector<cv::Point> v (points);

		m.insert( std::pair<ushort, std::vector<cv::Point> > (label,v));

		

		}

	


	}

	
	return m;
}

std::vector<cv::RotatedRect> CCL::getRotatedRect(std::map<ushort, std::vector<cv::Point> > m){

	  std::map<ushort,std::vector<cv::Point> >::iterator it;
	  
	  std::vector<cv::RotatedRect> rotated_rectangles;
	 
	   int puter = 0;
  
	  for (it = m.begin(); it!=m.end(); ++it)
		  {
		  	/* code */

		  	// create rotated bounding box

		  	std::vector<cv::Point> test = m[it->first];

		  	cv::RotatedRect rotated_rectangle = cv::minAreaRect(cv::Mat(test));

		  	rotated_rectangles.push_back(rotated_rectangle);
	 }

	 return rotated_rectangles;

}

std::vector<cv::Rect> CCL::getRect(std::vector<cv::RotatedRect> rotated_rectangles){

	  std::vector<cv::Rect> rectangles;

	  for (int i = 0; i < rotated_rectangles.size(); ++i)
	  {
	  	/* code */
	  	cv::Rect brect = rotated_rectangles.at(i).boundingRect();


	  

	  	rectangles.push_back(brect);

		
	  }

	  return rectangles;

}

std::vector<cv::Point> CCL::getComponentPoints(cv::Mat img){
	
	std::vector<cv::Point> pixel_points;

	for (int y = 0; y < img.rows; ++y)
	{
		/* code */
		for (int x = 0; x < img.cols; ++x)
		{
			/* code */
			cv::Scalar s = img.at<uchar>(y,x);

			int val = (int)s.val[0];

			if(val < 255){
				cv::Point p;

				p.x = x;
				p.y = y;

				pixel_points.push_back(p);
			}
		}
	}

	return pixel_points;


}

cv::RotatedRect CCL::getRotatedRect(std::vector<cv::Point> pixel_points){
	
	cv::RotatedRect box = cv::minAreaRect(pixel_points);



	

	return box;



}

cv::Mat CCL::visualizeRotatedRect(cv::RotatedRect rotated_rectangle,cv::Mat img){

	cv::Mat visual = img.clone();
	
	cv::Point2f vertices[4];

	 rotated_rectangle.points(vertices);
  	 
  	 for(int i = 0; i < 4; ++i){

  	 	cv::line(visual, vertices[i], vertices[(i + 1) % 4], cv::Scalar(0));

  	 }
    
 	return visual;   
}

std::vector< std::vector<cv::Point> > CCL::getConvexHulls(std::map<ushort, std::vector<cv::Point> > m){
		
		std::map<ushort,std::vector<cv::Point> >::iterator it;
	  	
	  	std::vector< std::vector<cv::Point> > hulls (m.size());
	 	
	 	int puter = 0;
	 
	  for (it = m.begin(); it!=m.end(); ++it)
		  {
				
				std::vector<cv::Point> test = m[it->first];
				
				cv::convexHull( cv::Mat(test), hulls[puter++], false );
		   }

    return hulls;
}

cv::Mat CCL::visualizeRect(std::vector<cv::Rect> rectangles, cv::Mat img){

	cv::Mat cobaGambar = img.clone();

	for (int i = 0; i < rectangles.size(); ++i)
	{
		/* code */
		cv::Rect r = rectangles.at(i);

		cv::rectangle(cobaGambar, r, cv::Scalar(0,0,0) );
	}

	
	
	return cobaGambar;


}

cv::Mat CCL::visualizeRect(cv::Rect rectangle, cv::Mat img){
	
	cv::Mat cobaGambar = img.clone();

	cv::rectangle(cobaGambar, rectangle, cv::Scalar(0) );

	return cobaGambar;
}

void CCL::sortRotatedRectangles(std::vector<cv::Rect>& rectangles){

	std::sort(rectangles.begin(),rectangles.end(),less_than_key());

}

cv::Mat CCL::filter(std::map<ushort,std::vector<cv::Point> > cc_points, double K, cv::Mat word_img){

std::map<ushort,std::vector<cv::Point> >::iterator it;

int maxp = 0;

for (it = cc_points.begin(); it!=cc_points.end(); ++it)
	{
		/* code */
		std::vector<cv::Point> points = std::vector<cv::Point>(it->second);

		if(points.size() > maxp){
			maxp = points.size();
		}
	}

std::map<ushort,std::vector<cv::Point> >::iterator it_min;


int minp = maxp;

for (it_min = cc_points.begin(); it_min!=cc_points.end(); ++it_min)
	{
		/* code */
		std::vector<cv::Point> points = std::vector<cv::Point>(it_min->second);

		if(points.size() < minp){
			minp = points.size();
		}
	}

std::map<ushort,std::vector<cv::Point> >::iterator it_a;


double maxa = 0;

for (it_a = cc_points.begin(); it_a!=cc_points.end(); ++it_a)
	{
		/* code */
		std::vector<cv::Point> points = std::vector<cv::Point>(it_a->second);

		cv::RotatedRect rotated_box = cv::minAreaRect(points);

		cv::Rect box = rotated_box.boundingRect();

		cv::Point x_y_min = box.tl();

		

		cv::Point x_y_max = box.br();

		double area = box.area();

		double a = (x_y_max.y - x_y_min.y) * 1.0;

		double b = (x_y_max.x - x_y_min.y) * 1.0;

		double c = a * b;

		

		double na = ((area*1.0)/(c*1.0));

		//std::cout << na << std::endl;

		if(na > maxa){
			maxa = na;
		}
		
	}

std::map<ushort,std::vector<cv::Point> >::iterator it_min_a;


double mina = maxa;

for (it_min_a = cc_points.begin(); it_min_a!=cc_points.end(); ++it_min_a)
	{
		/* code */
		std::vector<cv::Point> points = std::vector<cv::Point>(it_min_a->second);

		cv::RotatedRect rotated_box = cv::minAreaRect(points);

		cv::Rect box = rotated_box.boundingRect();

		cv::Point x_y_min = box.tl();

		cv::Point x_y_max = box.br();

		double area = box.area();

		double a = (x_y_max.y - x_y_min.y) * 1.0;

		double b = (x_y_max.x - x_y_min.y) * 1.0;

		double c = a * b;

		double na = ((area*1.0)/(c*1.0));
		

		if(na < mina){
			mina = na;
		}
		
	}


std::map<ushort,std::vector<cv::Point> >::iterator it_filter;

//std::cout << maxa << " " << mina << std::endl;

int bb_ke = 1;

std::vector<uchar> index_bb_outliers;

for (it_filter = cc_points.begin(); it_filter!=cc_points.end(); ++it_filter)
	{
		/* code */
		std::vector<cv::Point> points = std::vector<cv::Point>(it_filter->second);

		int np = points.size();

		double TP = (np - minp)*1.0 / (maxp - minp)*1.0;

		cv::RotatedRect rotated_box = cv::minAreaRect(points);

		cv::Rect box = rotated_box.boundingRect();

		cv::Point x_y_min = box.tl();

		cv::Point x_y_max = box.br();

		double area = box.area();

		double a = (x_y_max.y - x_y_min.y) * 1.0;

		double b = (x_y_max.x - x_y_min.y) * 1.0;

		double c = a * b;

		double na = ((area*1.0)/(c*1.0));
		

		double TA = (na - mina)*1.0 / (maxa - mina)*1.0;

		if(TA < K || TP < K){
			index_bb_outliers.push_back(it_filter->first);
		}
		//std::cout << TA << std::endl;

		bb_ke++;

	}

cv::Mat hasil_filter = word_img.clone();

for (int i = 0; i < index_bb_outliers.size(); ++i)
{
	/* code */
	//std::cout << (int)index_bb_outliers.at(i) << std::endl;
	std::vector<cv::Point> points = std::vector<cv::Point>(cc_points[index_bb_outliers.at(i)]);

	for (int p = 0; p < points.size(); ++p)
	{
		/* code */
		cv::Point point = points.at(p);

		hasil_filter.at<uchar>(point.y,point.x) = 255;
	}
}




return hasil_filter;

}	

