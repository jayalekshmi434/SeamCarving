#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include<opencv4/opencv2/highgui.hpp>
#include<opencv4/opencv2/imgproc.hpp>
#include<opencv4/opencv2/core.hpp>

class Image{

    private:
        
       
    
    public:

        int height;
        int width;
        enum carveMode {VERTICAL_ADD,VERTICAL_TRIM,HORIZONTAL_ADD,HORIZONTAL_TRIM};
        enum direction {VERTICAL,HORIZONTAL};
        
        cv::Mat image;
        cv::Mat grayScale;
        cv::Mat paddedImg;
        Image(std::string path);
        Image(cv::Mat img);
        Image ();
        void resize();
        void convertToGrayScale();
        cv::Mat calculateEnergy(cv::Mat& ); 
        void calculateCumulativePixels(int, int ,cv::Mat &,cv::Mat &);
        cv::Mat getEnergyMap(cv::Mat&,direction);    
        cv::Mat getEnergyMap(cv::Mat&);    
        std::vector<int> getLowestEnergyPath(cv::Mat &,direction) ;
        std::vector<int>getLowestEnergyPathHorizontal(cv::Mat) ;
        std::vector<int> getSeamToRemove(cv::Mat&,direction);
        cv::Mat addSeam(cv::Mat &,std::vector<int>);
        cv::Mat removeVerticalSeam(cv::Mat &);
        cv::Mat removeHorizontalSeam(cv::Mat &);
        cv::Mat addHorizontalSeam(cv::Mat &);
        cv::Mat addVerticalSeam(cv::Mat &);
        cv::Mat seamcarve(cv::Mat& img, carveMode);
};