#include "Seamcarver.h"

Seamcarver::Seamcarver(){
    std::cout << "Seam Carver Initilialized";
}

void Seamcarver::setTrackbar(int width , int x){
    width= width;
    val=x;
   

}
void Seamcarver::carve(std::string path){
    Image img(path);
    img.resize();
    cv::imshow("originalImage",img.image);
    bool running =true;

    cv::Mat resizedImg=img.image.clone(); 
    cv::imshow("resizedImage",resizedImg);
    cv::Mat temp;
    int c= cv::waitKey();
        while(c==100 || c==117 || c==108 ||c==114){
            
          if(c==100){ //down
                    temp=img.seamcarve(resizedImg,Image::carveMode::HORIZONTAL_TRIM);

          } else if(c==117){  
                    //up
                   temp=img.seamcarve(resizedImg,Image::carveMode::HORIZONTAL_ADD);
          }
            else if(c==108)
                    // left
                    temp=img.seamcarve(resizedImg,Image::carveMode::VERTICAL_TRIM);
             else if(c==114)
                //right
                    temp=img.seamcarve(resizedImg,Image::carveMode::VERTICAL_ADD);
              else{
                std::cout << "Invalid key Press";
              }
                    
            
            resizedImg.release();
            temp.copyTo(resizedImg);
            temp.release();
            cv::imshow("resizedImage",resizedImg);
            c=cv::waitKey(0);
            
        }
        c=cv::waitKey(0);
}
     