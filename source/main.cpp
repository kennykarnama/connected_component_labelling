#include "ccl.h"
#include "projection.h"
#include "skew.h"

void displayImage(std::string namaWindow, int jenisWindow, cv::Mat gambarnya);


int main(int argc, char const *argv[])
{
	/* code */

	cv::Mat word_img = cv::imread(argv[1],CV_LOAD_IMAGE_ANYDEPTH);

	std::string nama_file(argv[2]);

	CCL ccl;

	cv::Mat word_img_cc = ccl.connectedComponentLabelling(word_img);

	std::vector<ushort>labels = ccl.getComponentLabels(word_img_cc);

	std::map<ushort,std::vector<cv::Point> > cc_points = ccl.getComponentPoints(labels,word_img_cc);

	std::vector<cv::RotatedRect> rotated_rects = ccl.getRotatedRect(cc_points);

	std::vector<cv::Rect> rects =  ccl.getRect(rotated_rects);


	cv::Mat visualisasi_bb_citra =  ccl.visualizeRect(rects, word_img);

	cv::Mat hasil_filter = ccl.filter(cc_points,0.002, word_img);

	Projection projection;

	

	Skew skew;

	// for (int i = -10; i <= 10; ++i)
	// {
	// 	/* code */
	// 		cv::Mat source = hasil_filter.clone();

	// 		cv::Point2f src_center(source.cols/2.0F, source.rows/2.0F);
	// 		cv::Mat rot_mat = cv::getRotationMatrix2D(src_center, i*1.0, 1.0);
	// 		cv::Mat dst;
	// 		cv::warpAffine(source, dst, rot_mat, source.size(),cv::INTER_CUBIC);

	// 		std::vector<int> proyeksi =  projection.projectVertical(dst);

	// 		std::vector<double> normalized =  projection.normalizeProjection(proyeksi);

	// 		std::vector<double> entropies =  skew.entropy(normalized);

	// 		std::vector<double> Eh =  skew.Eh(entropies);

			
			
	// 		double E = skew.E(Eh);

	// 		std::cout.precision(10);

	// 		std::cout << E << std::endl;

	// 	// 	//std::vector<int> vertical_projection = projection.projectVertical(dst);
	// 	// 	 proyeksi =  projection.projectVertical(dst);

	// 	// for (int i = 0; i < E.size(); ++i)
	// 	// {
	// 	// 	 code 
	// 	// 	std::cout << E.at(i) << std::endl;
	// 	// }

	// }

	// for (double i = 0.0; i <= 2.1; i+=0.1)
	// {
	// 	/* code */
	// 		cv::Mat source = hasil_filter.clone();

	// 		cv::Point2f src_center(source.cols/2.0F, source.rows/2.0F);
	// 		cv::Mat rot_mat = cv::getRotationMatrix2D(src_center, i*1.0, 1.0);
	// 		cv::Mat dst;
	// 		cv::warpAffine(source, dst, rot_mat, source.size());

	// 		std::vector<int> proyeksi =  projection.projectVertical(dst);

	// 		std::vector<double> normalized =  projection.normalizeProjection(proyeksi);

	// 		std::vector<double> entropies =  skew.entropy(normalized);

	// 		std::vector<double> Eh =  skew.Eh(entropies);

			
			
	// 		double E = skew.E(Eh);

	// 		std::cout.precision(10);

	// 		std::cout << E << std::endl;

	// 	// 	//std::vector<int> vertical_projection = projection.projectVertical(dst);
	// 	// 	 proyeksi =  projection.projectVertical(dst);

	// 	// for (int i = 0; i < E.size(); ++i)
	// 	// {
	// 	// 	 code 
	// 	// 	std::cout << E.at(i) << std::endl;
	// 	// }

	// }

	cv::Mat source = hasil_filter.clone();

			cv::Point2f src_center(source.cols/2.0F, source.rows/2.0F);
			cv::Mat rot_mat = cv::getRotationMatrix2D(src_center, 0.9, 1.0);
			cv::Mat dst;
			cv::warpAffine(source, dst, rot_mat, source.size());

	
		

		displayImage("word_img",CV_WINDOW_KEEPRATIO,dst);

		 imwrite(nama_file+".png",dst);
	
	return 0;
}

void displayImage(std::string namaWindow, int jenisWindow, cv::Mat gambarnya){
	
	cv::namedWindow(namaWindow,jenisWindow);

	cv::imshow(namaWindow,gambarnya);

	cv::waitKey(0);

}