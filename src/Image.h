#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include<opencv4/opencv2/highgui.hpp>
#include<opencv4/opencv2/imgproc.hpp>
#include<opencv4/opencv2/core.hpp>

class Image{

    private:
        int height;
        int width;
        enum carveMode {VERTICAL,HORIZONTAL};
    
    public:
        cv::Mat image;
        cv::Mat grayScale;
        Image(std::string path);
        Image(cv::Mat img);
        void resize();
        cv::Mat addPaddingToImage();
        void convertToGrayScale();
        cv::Mat calculateEnergy(cv::Mat& ); 
        void calculateCumulativePixels(int, int ,cv::Mat &,cv::Mat &);
        cv::Mat getEnergyMap(cv::Mat&);     
        std::vector<int> getSeamToRemove(cv::Mat&,carveMode);
};