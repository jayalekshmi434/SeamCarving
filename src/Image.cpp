#include "Image.h"

Image::Image(std::string path){
    
    image =cv::imread(path);
    cv::Size sz=image.size();
    height = sz.height;
    width= sz.width;
    
    
}
Image::Image(){
    
    
    
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

void Image::addPaddingToImage(){

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

    paddedImg= paddedImage;

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
    int v= cv::waitKey(0);
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
    return energyMap;
}

std::vector<int> Image::getLowestEnergyPath(cv::Mat &eMap){
    
    int rows=eMap.rows;
    std::vector<int> seam(rows);
    std::vector<double> backTrack(3);

    //get min val index in last row

    cv::Point minIdxPointr;
    cv::Mat temp=eMap.row(eMap.rows-1);
    cv::minMaxLoc(temp,nullptr,nullptr,&minIdxPointr,nullptr);
    int idx= minIdxPointr.x;
    seam[eMap.rows-1]=idx;

    //now back track to get seam
    
    for(int r=eMap.rows-2;r>=0;r--){
        backTrack[0]=eMap.at<uchar>(r,std::max(idx-1,0));
        backTrack[1]=eMap.at<uchar>(r,idx);
        backTrack[2]=eMap.at<uchar>(r,std::min(idx+1,eMap.cols-1));
        int offset=0;
        //find min indx
        
        int minIdx=std::min_element(backTrack.begin(),backTrack.end())-backTrack.begin();
        
        if(minIdx==0){
            offset=-1;
        } else if(minIdx== 1){
            offset=0;
        } else{
            offset=1;
        }
        
        idx=idx+offset;
        seam[r]=std::min(std::max(idx,0),eMap.cols-1);

    }
  

    return seam;

}

std::vector<int> Image::getSeamToRemove(cv::Mat &energyMap,Image::carveMode direction) {
   
   
    cv::Mat source;
    cv::Mat cumulativeEnergyMap;
    std::vector<int> lowestEnergyPath;

    // Rotate the image to operate horzontally
    if (direction == HORIZONTAL_ADD || HORIZONTAL_TRIM) {
        cv::rotate(energyMap, source, cv::ROTATE_90_CLOCKWISE);
    } else {
        source = energyMap;
    }

    cumulativeEnergyMap = getEnergyMap(source);
    lowestEnergyPath = getLowestEnergyPath(cumulativeEnergyMap);

    return lowestEnergyPath;
}

cv::Mat Image::removeSeam(cv::Mat &img,std::vector<int>seam ){
    //create a Mat
    cv::Mat modifiedImage =cv::Mat(img.rows,img.cols-1,img.type(),double(0));
    cv::Mat tempL,tempR,temp;
    for(int r=0;r<img.rows;r++){
         img(cv::Range(r,r+1), cv::Range(0,seam[r])).copyTo(tempL);
         img(cv::Range(r,r+1),cv::Range(seam[r]+1,img.cols)).copyTo(tempR);
         if (tempL.empty()) {
            temp = tempR;
        } else if (tempR.empty()) {
            temp = tempL;
        } else {
            cv::hconcat(tempL,tempR,temp);
        }

        temp.copyTo(modifiedImage.row(r));
    }

    return modifiedImage;

}

cv::Mat Image::addSeam(cv::Mat &img , std::vector<int>seam){
    cv::Mat modifiedImage(img.rows, img.cols+1, CV_8UC3, cv::Scalar(0, 0, 0));
		
			int max = img.rows-1;
			int width=0;
			for (int h = 0; h < img.rows; h++)
			{
				for (int w = 0; w < img.cols; w++)
				{
					// duplicate best seam
					if (w == seam[h])
					{
						modifiedImage.at<cv::Vec3b>(h, w) = img.at<cv::Vec3b>(h, width);
						modifiedImage.at<cv::Vec3b>(h, w+1) = img.at<cv::Vec3b>(h, width);
						w++;
					
					}
					else
					{
						modifiedImage.at<cv::Vec3b>(h, w) = img.at<cv::Vec3b>(h, width);
					}
                    width++;
				}
				width = 0;
            }
   

    return modifiedImage;
   

}

cv::Mat Image::addHorizontalSeam(cv::Mat &img , std::vector<int>seam){

    cv:: cvtColor(img,grayScale,cv::COLOR_BGR2GRAY);
    cv::Mat eMap =calculateEnergy(grayScale);
	std::vector<int>seam1=getSeamToRemove(eMap,HORIZONTAL_ADD);
    std::cout << "reached Here also"<<std::endl;
    cv::Mat rotatedImg,modImg;
    
    cv::Mat modifiedImage(img.rows+1, img.cols, CV_8UC3, cv::Scalar(0, 0, 0));
	cv::Mat img_new(img.rows+1, img.cols, CV_8UC3, cv::Scalar(0, 0, 0));
			int max = width - 1;
			int hh = 0;
			for (int w = 0; w < img.cols; w++)
			{
				for (int h = 0; h < img.rows; h++)
				{
					// duplicate best seam
					if (h == seam1[w])
					{
						img_new.at<cv::Vec3b>(h, w) = img.at<cv::Vec3b>(hh, w);
						img_new.at<cv::Vec3b>(h+1, w) = img.at<cv::Vec3b>(hh, w);
						h++;
						hh++;
					}
					else
					{
						img_new.at<cv::Vec3b>(h, w) = img.at<cv::Vec3b>(hh, w);
						hh++;
					}
				}
				hh = 0;
				max--;
			}	
			
    return img_new;
   

}

cv::Mat Image ::removeverticalSeam(cv::Mat &img,std::vector<int>seam){
    return Image::removeSeam(img,seam);
}

cv::Mat Image ::removeHorizontalSeam(cv::Mat &img,std::vector<int>seam){
    cv::Mat rotatedImg,modImg;
    cv::rotate(img,rotatedImg,cv::ROTATE_90_CLOCKWISE);
    modImg=Image::removeSeam(rotatedImg,seam);
    cv::rotate(modImg,modImg,cv::ROTATE_90_COUNTERCLOCKWISE);
    return modImg;
}

cv::Mat Image ::addVerticalSeam(cv::Mat &img,std::vector<int>seam){
    return Image::addSeam(img,seam);
}

cv::Mat Image ::addHorizontalSeam(cv::Mat &img,std::vector<int>seam, bool rotate){
    cv::Mat rotatedImg,modImg;
    cv::rotate(img,rotatedImg,cv::ROTATE_90_CLOCKWISE);
    modImg=addSeam(rotatedImg,seam);
    cv::rotate(modImg,modImg,cv::ROTATE_90_COUNTERCLOCKWISE);
    return modImg;
}

cv::Mat Image::seamcarve(cv::Mat& img, carveMode mode){
     cv:: cvtColor(img,grayScale,cv::COLOR_BGR2GRAY);
     cv::Mat eMap =calculateEnergy(grayScale);
	 std::vector<int>seam=getSeamToRemove(eMap,mode);
     cv::Mat modImg;
     switch(mode){
         case VERTICAL_TRIM:
            modImg=removeverticalSeam(img,seam);
            break;
        case HORIZONTAL_TRIM:
            modImg=removeHorizontalSeam(img,seam);
            break;
        case HORIZONTAL_ADD:
            modImg=addHSeam(img,seam);
            break;
        case  VERTICAL_ADD :
            modImg=addVerticalSeam(img,seam);
            break;
            
     }
     return modImg;
}