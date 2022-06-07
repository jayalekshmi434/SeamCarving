#include "Image.h"

Image::Image(std::string path){
    
    image =cv::imread(path);
    cv::Size sz=image.size();
    height = sz.height;
    width= sz.width;
    
    
}

void Image::resize(){
    cv::resize(image,image,cv::Size(650,400));
    cv::Size sz=image.size();
    height = sz.height;
    width= sz.width;
    
}

void  Image::convertToGrayScale(){
    cv:: cvtColor(image,grayScale,cv::COLOR_BGR2GRAY);
}

cv::Mat Image::addPaddingToImage(){

    int paddingWidth=2;
    int paddingHeight=2;
    cv::Mat paddedImage(height+paddingHeight,width+paddingWidth,CV_8UC1,cv::Scalar(0));   

    //copy grayScaleImage to centre of paddedImage

    for(int i =1; i< height ; i++){
       for(int j=0;j<width;j++){
            paddedImage.at<uchar>(i+1,j+1)=grayScale.at<uchar>(i,j);
        }
    }

    //duplicate first column and lst column
    for(int i =0; i< height+2;i++){
        paddedImage.at<uchar>(i+1,0)=grayScale.at<uchar>(i,0);
        paddedImage.at<uchar>(i+1,width+1)=grayScale.at<uchar>(i,width-1);
    }

    // duplicate fist row and last row
    for(int i =0; i< width+2;i++){
        paddedImage.at<uchar>(0,i+1)=grayScale.at<uchar>(0,i);
        paddedImage.at<uchar>(height+1,i+1)=grayScale.at<uchar>(height-1,i);
    }
    
    //duplicate the corners
    paddedImage.at<uchar>(0,0)=grayScale.at<uchar>(0,0);
    paddedImage.at<uchar>(0,width+1)=grayScale.at<uchar>(0,width-1);
    paddedImage.at<uchar>(height+1,0)=grayScale.at<uchar>(height-1,0);
    paddedImage.at<uchar>(height+1,width+1)=grayScale.at<uchar>(height-1,width-1);

    return paddedImage;

}

cv::Mat Image::calculateEnergy(cv::Mat &source){


    const static int sobelDelta_ = 0;
    const static int sobelScale_ = 1;
    cv::Size blurKernel = cv::Size(5,5);

    cv::Mat xGradient, yGradient, target;
    cv::GaussianBlur(source, target, blurKernel, 0, 0, cv::BORDER_DEFAULT);

    // Calculate gradient using sobel filters
    cv::Sobel(target, xGradient, CV_16S, 1, 0, 3, sobelScale_, sobelDelta_,
              cv::BORDER_DEFAULT);
    cv::convertScaleAbs(xGradient, xGradient);
   cv::Sobel(target, yGradient, CV_16S, 0, 1, 3, sobelScale_, sobelDelta_,
             cv::BORDER_DEFAULT);
   cv::convertScaleAbs(yGradient, yGradient);

    cv::addWeighted(xGradient, 0.5, yGradient, 0.5, 0, target);
    target.convertTo(target, CV_64F, 1.0/255.0);
    return target;

    
}

void Image::calculateCumulativePixels(int r, int c ,cv::Mat &energyMat,cv::Mat &energyMap){
    double left,mid,right;
    left=energyMap.at<uchar>(r-1,std::max(c-1,0));
    mid = energyMap.at<uchar>(r-1,c);
    right=energyMap.at<uchar>(r-1,std::min(c+1,energyMat.cols-1));
    energyMap.at<uchar>(r,c)=energyMat.at<uchar>(r,c)+std::min(left,std::min(mid,right));
}

cv::Mat Image::getEnergyMap(cv::Mat &energyMat){
    cv::Mat energyMap = cv::Mat(energyMat.rows,energyMat.cols,CV_64F,double(0));
    energyMat.row(0).copyTo(energyMap.row(0));
    // Add concurrency
    for(int r=1;r<energyMat.rows;r++){
        for(int c= 0;c<energyMat.cols;c++){
           calculateCumulativePixels(r,c,energyMat,energyMap);
        }
    }
}

std::vector<int> Image::getSeamToRemove(cv::Mat &energyMap,Image::carveMode direction) {
   
   
    cv::Mat source;
    cv::Mat cumulativeEnergyMap;
    cv::Mat result;
    std::vector<int> lowestEnergyPath;

    // Rotate the image to operate horzontally
    if (direction == HORIZONTAL) {
        cv::rotate(energyMap, source, cv::ROTATE_90_CLOCKWISE);
    } else {
        source = energyMap;
    }

    cumulativeEnergyMap = getEnergyMap(source);
   // lowestEnergyPath = calculateLowestEnergyPath(cumulativeEnergyMap);

    return lowestEnergyPath;
}