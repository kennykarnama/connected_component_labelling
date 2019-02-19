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

	cv::Mat cclIzed = ccl.visualize(word_img_cc);

	displayImage("ccl", CV_WINDOW_KEEPRATIO, cclIzed);
	
	return 0;
}

void displayImage(std::string namaWindow, int jenisWindow, cv::Mat gambarnya){
	
	cv::namedWindow(namaWindow,jenisWindow);

	cv::imshow(namaWindow,gambarnya);

	cv::waitKey(0);

}