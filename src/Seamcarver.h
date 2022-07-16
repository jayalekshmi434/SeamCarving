
#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include<opencv4/opencv2/highgui.hpp>
#include<opencv4/opencv2/imgproc.hpp>
#include<opencv4/opencv2/core.hpp>
#include"Image.h"



#define WINDOW_NAME "Resized Image"


class Seamcarver{
    public:
    int width;
    int val;
    Seamcarver();
    void setTrackbar(int width , int x);
   
   
    void carve(std::string );
    
};