#include "projection.h"

Projection::Projection(){

}

Projection::~Projection(){

}

std::vector<int> Projection::projectVertical(cv::Mat img){

	int row = img.rows;

	int col = img.cols;

	// buat vector 

	std::vector<int> proj;

	for(int r=0;r<row;r++){
		proj.push_back(0);
	}

	double cumul;

	for(int i=0;i<row;i++){

		cumul = 0;
		
		for(int j=0;j<col;j++){

			cv::Scalar intensity = img.at<uchar>(i,j);

			// uchar uVal = intensity;

			int val = (int) intensity.val[0];

			if(val == 0){

				cumul++;

			}

		}

		proj[i] = cumul;
	}

	return proj;

}

cv::Mat Projection::getImgVerProj(std::vector<int> verticalVector, cv::Mat img){

	// bentuk template sebesar row x col

	int row = img.rows;

	int col = img.cols;

	cv::Mat projected(row,col,CV_8UC1,cv::Scalar::all(255));

	for(int i=0;i<row;i++){

		int val = verticalVector.at(i);
		
		for(int j=0;j<val;j++){
			projected.at<uchar>(i,j) = 0;
		}

	}

	return projected;

}

std::vector<int> Projection::projectHorizontal(cv::Mat img){
	// iterate over column


	int row = img.rows;

	int col = img.cols;

	std::vector<int> projected;

	for(int c=0;c<col;c++){
		projected.push_back(0);
	}


	for(int x = 0; x < col; x++){

		cv::Mat colMat = img.col(x);

		cv::Scalar s = colMat.at<uchar>(0,0);

		//cout << colMat.rows<< " "<<colMat.cols << endl;

		//cout << (int)s.val[0]<<endl;

		
		int sum = 0;


		for(int a = 0; a < colMat.rows; a++ ){
			for(int b = 0; b < colMat.cols; b++){
				
				cv::Scalar s = colMat.at<uchar>(a,b);

				//uchar uVal = s.val[0];

				int val = (int) s.val[0];

				//cout << val << endl;

				if(val < 255){
					sum++;
				}

			}
		}

		projected[x] = sum;
		//projected[x] = blacks;

	}

	return projected;
}

cv::Mat Projection::getImgHorProj(std::vector<int> horizontalVector, cv::Mat img){
	// bentuk template sebesar row x col

	int row = img.rows;

	int col = img.cols;

	cv::Mat projected(row,col,CV_8UC1,cv::Scalar::all(255));

	

	for(int x = 0; x < col; x++){

		// projected.col(x).at<uchar>(0,0);

		int batas = horizontalVector.at(x);

		for(int i=row-1;i>=(row-batas);i--){
			
			for(int j=0;j<img.col(x).cols;j++){
				projected.col(x).at<uchar>(i,j) = 0;
			}
		}


	}

	return projected;
}

std::vector<double> Projection::normalizeProjection(std::vector<int> projection){

	double maksimum = *max_element(projection.begin(),projection.end());

	std::vector<double> normalized;

	for (int i = 0; i < projection.size(); ++i)
	{
		/* code */
		double norm = (projection.at(i)*1.0)/(maksimum*1.0);

		if(norm == 0){
			norm = 1;
		}

		normalized.push_back(norm);
	}

	return normalized;
}