#include "Seamcarver.h"

Seamcarver::Seamcarver(bool running_):running(running_){
    std::cout << "Seam Carver Initilialized";
}


void Seamcarver::carve(std::string path){
    //Image img(path);
    img =std::make_unique< Image>(path);
    img->resize();
    cv::imshow("originalImage",img->image);
  
    cv::Mat resizedImg=img->image.clone(); 
    cv::imshow("resizedImage",resizedImg);
    cv::Mat tempImg;
    int c= cv::waitKey();
        while(c==100 || c==117 || c==108 ||c==114){
            
          if(c==100){ //down
                    tempImg=img->seamcarve(resizedImg,Image::carveMode::HORIZONTAL_TRIM);

          } else if(c==117){  
                    //up
                   tempImg=img->seamcarve(resizedImg,Image::carveMode::HORIZONTAL_ADD);
          }
            else if(c==108)
                    // left
                    tempImg=img->seamcarve(resizedImg,Image::carveMode::VERTICAL_TRIM);
             else if(c==114)
                //right
                    tempImg=img->seamcarve(resizedImg,Image::carveMode::VERTICAL_ADD);
              else{
                std::cout << "Invalid key Press";
              }
                    
            
            resizedImg.release();
            tempImg.copyTo(resizedImg);
            tempImg.release();
            cv::imshow("resizedImage",resizedImg);
            c=cv::waitKey(0);
            
        }
        c=cv::waitKey(0);
}

Seamcarver::~Seamcarver(){
   running = false;
   img.release();
  
}