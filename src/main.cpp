#include "stdio.h"
#include <iostream>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>


#include "Image.h"
#include "detectKey.h"

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name 
              << "\t--image SOURCE_PATH \t EXAMPLE --image../Data/index.jpg"
              << std::endl;
}


int main (int argc,char* argv[]) {

	if (argc < 2) { // We expect 2 arguments: the program name, the image source path
        show_usage(argv[0]);
		return 1;
    }

	std::string path;
	if (std::string(argv[1]) == "--image") {
		path = argv[2];
	} else {
		show_usage(argv[0]);
		return 1;
	}
	

	Image img(path);
	//img.resize();
	img.convertToGrayScale();
	img.addPaddingToImage();
	cv::Mat target=img.calculateEnergy(img.grayScale);
	cv::imshow("energy Matrix",target);

	/*
	
	
	
	///cv::imshow(img);
	int c = cv::waitKey(0);


	detectKey key;
	bool run = true;
	//key.handleInput(run);
	*/
	int c = cv::waitKey(0);
	return 0;

}

