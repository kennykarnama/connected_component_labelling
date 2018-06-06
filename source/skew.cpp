#include "skew.h"

Skew::Skew(){

}

Skew::~Skew(){

}


std::vector<double> Skew::entropy(std::vector<double> normalized_vertical_projection){

	std::vector<double> all_element_entropies;
	
	for (int i = 0; i < normalized_vertical_projection.size(); ++i)
	{
		/* code */
		double entropy = (-1.0*normalized_vertical_projection.at(i))*log10(normalized_vertical_projection.at(i));

		all_element_entropies.push_back(entropy);
	}

	return all_element_entropies;
	

}

std::vector<double> Skew::Eh(std::vector<double> entropies){
	
	std::vector<double> e(entropies.size());

	for (int i = 0; i < entropies.size(); ++i)
	{
		/* code */
		int m = entropies.size()-1;

		double sum = 0.0;

		for (int start = i; start <= m; ++start)
		{
			/* code */
			sum+=entropies.at(start)*1.0;
		}

		e[i] = sum;
	}


	return e;
}

double Skew::E(std::vector<double> E){
	double sum = 0.0;

	for (int i = 0; i < E.size(); ++i)
	{
		/* code */
		sum+=E.at(i)*1.0;
	}


	return (sum*1.0)/(E.size());
}

std::vector<double> Skew::deskew(int start,int end,cv::Mat img){

	cv::Mat source = img.clone();

	
	Projection projection;

	std::vector<double> entropies;

	for (int i = start; i <= end ; ++i)
	{
		/* code */

		cv::Point2f src_center(source.cols/2.0F, source.rows/2.0F);
		cv::Mat rot_mat = cv::getRotationMatrix2D(src_center, i*1.0, 1.0);
		cv::Mat dst;
		cv::warpAffine(source, dst, rot_mat, source.size(),cv::INTER_CUBIC);

		std::vector<int> vertical_projection = projection.projectVertical(dst);

		
		double maks = -1;

		for (int i = 0; i < vertical_projection.size(); ++i)
		{
			/* code */
			double a = (vertical_projection.at(i)) * log(vertical_projection.at(i));

			if(a > maks){
				maks = a;
			}

		}

		entropies.push_back(maks);

		
	}
	
	return entropies;

}

std::vector<double> Skew::deskew(double start,double end,cv::Mat img){
	
	cv::Mat source = img.clone();

	std::vector<double> entropies;

	Projection projection;

	for (double i = start; i <= end ; i+=0.1)
	{
		/* code */
		//std::cout << i << std::endl;

		cv::Point2f src_center(source.cols/2.0F, source.rows/2.0F);
		cv::Mat rot_mat = cv::getRotationMatrix2D(src_center, i*1.0, 1.0);
		cv::Mat dst;
		cv::warpAffine(source, dst, rot_mat, source.size());

		std::vector<int> vertical_projection = projection.projectVertical(dst);

		double maks = -1;

		for (int i = 0; i < vertical_projection.size(); ++i)
		{
			/* code */
			double a = (vertical_projection.at(i)) * log(vertical_projection.at(i));

			if(a > maks){
				maks = a;
			}

		}

		entropies.push_back(maks);

		

	}
	
	return entropies;
}

int Skew::potential_angle(int a,int b,std::vector<double> entropies){


	int maks = entropies.at(0);


	int indeks = a;

	for (int i = 0; i < entropies.size(); ++i)
	{
		/* code */
		if(maks < entropies.at(i)){
			maks = entropies.at(i);

			indeks = (a+i);
		}
	}

	return indeks;


}

