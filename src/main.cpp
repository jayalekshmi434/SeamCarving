


#include "stdio.h"
#include <iostream>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>



#include "Seamcarver.h"

cv::Mat original;
int val;

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
	

	
	Seamcarver seamcarver(true);
	seamcarver.carve(path);  

	return 0;

}

