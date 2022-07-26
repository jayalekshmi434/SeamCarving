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


cv::Mat Image::calculateEnergy(cv::Mat &source){


    const static int sobelDelta_ = 0;
    const static int sobelScale_ = 1;
    cv::Size blurKernel = cv::Size(3,3);

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
    left=energyMap.at<double>(r-1,std::max(c-1,0));
    mid = energyMap.at<double>(r-1,c);
    right=energyMap.at<double>(r-1,std::min(c+1,energyMat.cols-1));
    energyMap.at<double>(r,c)=energyMat.at<uchar>(r,c)+std::min(left,std::min(mid,right));
}

cv::Mat Image::getEnergyMap(cv::Mat &energy_image,direction seam_direction){
   
    double a,b,c;

    int rowsize = energy_image.rows;
    int colsize = energy_image.cols;
    
    // initialize the map with zeros
    cv::Mat cumulativeEnergymap = cv::Mat(rowsize, colsize, CV_64F, double(0));
    
    // copy the first row
    if (seam_direction == VERTICAL) {
        energy_image.row(0).copyTo(cumulativeEnergymap.row(0));
    } else if (seam_direction == HORIZONTAL) {
        energy_image.col(0).copyTo(cumulativeEnergymap.col(0));
    }
   
    if (seam_direction == VERTICAL) {
         
        for (int row = 1; row < rowsize; row++) {
            for (int col = 0; col < colsize; col++) {
                a = cumulativeEnergymap.at<double>(row - 1, std::max(col - 1, 0));
                b = cumulativeEnergymap.at<double>(row - 1, col);
                c = cumulativeEnergymap.at<double>(row - 1,std:: min(col + 1, colsize - 1));
                
                cumulativeEnergymap.at<double>(row, col) = energy_image.at<double>(row, col) + std::min(a, std::min(b, c));
                
            }
        }
    }
    else if (seam_direction == HORIZONTAL) {
        for (int col = 1; col < colsize; col++) {
            for (int row = 0; row < rowsize; row++) {
                a = cumulativeEnergymap.at<double>(std::max(row - 1, 0), col - 1);
                b = cumulativeEnergymap.at<double>(row, col - 1);
                c = cumulativeEnergymap.at<double>(std::min(row + 1, rowsize - 1), col - 1);
                cumulativeEnergymap.at<double>(row, col) = energy_image.at<double>(row, col) + std::min(a, std::min(b, c));
                
            }
        }
    }
     
    return cumulativeEnergymap;
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
std::vector<int> Image::getLowestEnergyPath(cv::Mat &eMap,direction direction){
    int rows=eMap.rows;
    int cols =eMap.cols;
    std::vector<int> seam;
    std::vector<double> backTrack(3);
    int offset=0;
    if(direction==VERTICAL){
        
        seam.resize(rows);
        
        cv::Point minIdxPointr;
        cv::Mat temp=eMap.row(eMap.rows-1);
        cv::minMaxLoc(temp,nullptr,nullptr,&minIdxPointr,nullptr);
        int idx= minIdxPointr.x;
        seam[eMap.rows-1]=idx;

        //now back track to get seam
        
        for(int r=eMap.rows-2;r>=0;r--){
            backTrack[0]=eMap.at<double>(r,std::max(idx-1,0));
            backTrack[1]=eMap.at<double>(r,idx);
            backTrack[2]=eMap.at<double>(r,std::min(idx+1,eMap.cols-1));
            
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
    } else {
       
        seam.resize(cols);
        cv::Point minIdxPointr;
        cv::Mat temp=eMap.col(cols-1);
        cv::minMaxLoc(temp,nullptr,nullptr,&minIdxPointr,nullptr);
        int idx= minIdxPointr.y;
        seam[eMap.cols-1]=idx;
        
        for (int c = cols - 2; c >= 0; c--) {
            backTrack[0] = eMap.at<double>(std::max(idx - 1, 0), c);
            backTrack[1] = eMap.at<double>(idx, c);
            backTrack[2] = eMap.at<double>(std::min(idx + 1, rows- 1), c);
            
            int minIdx=std::min_element(backTrack.begin(),backTrack.end())-backTrack.begin();
            
            if(minIdx==0){
                offset=-1;
            } else if(minIdx== 1){
                offset=0;
            } else{
                offset=1;
            }
            
            idx=idx+offset;
            seam[c] = std::min(std::max(idx, 0), cols - 1); 
           
    }
    return seam;
    }

}

std::vector<int> Image::getSeamToRemove(cv::Mat &energyMap,Image::direction direction) { 
    cv::Mat source;
    cv::Mat cumulativeEnergyMap;
    std::vector<int> lowestEnergyPath;
    cumulativeEnergyMap= getEnergyMap(energyMap,direction);
    lowestEnergyPath=getLowestEnergyPath(cumulativeEnergyMap,direction);    
    return lowestEnergyPath;
}

cv::Mat Image ::removeVerticalSeam(cv::Mat &img){
    cv:: cvtColor(img,grayScale,cv::COLOR_BGR2GRAY);
    cv::Mat eMap =calculateEnergy(grayScale);
	std::vector<int>seam=getSeamToRemove(eMap,VERTICAL);
    cv::Mat modifiedImage(img.rows, img.cols-1, CV_8UC3, cv::Scalar(0, 0, 0));
			
    int colsIndex = img.rows - 1;
	int imgWidth = 0;
	for (int h = 0; h < modifiedImage.rows; h++)
		{
		for (int w = 0; w < modifiedImage.cols; w++)
			{
			 if (w == seam[colsIndex])
			 {
						imgWidth++;
			 }
			modifiedImage.at<cv::Vec3b>(h, w) = img.at<cv::Vec3b>(h, imgWidth);
			imgWidth++;
				}
				colsIndex--;
				imgWidth = 0;
			}
            return modifiedImage;
}

cv::Mat Image ::removeHorizontalSeam(cv::Mat &img){
    cv:: cvtColor(img,grayScale,cv::COLOR_BGR2GRAY);
    cv::Mat eMap =calculateEnergy(grayScale);
	std::vector<int>seam=getSeamToRemove(eMap,HORIZONTAL);
    cv::Mat modifiedImage(img.rows-1, img.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    
	int rowsIndex = img.cols- 1;
	int orgHeight = 0;
	for (int w = 0; w <modifiedImage.cols; w++)
			{
		for (int h = 0; h < modifiedImage.rows; h++)
		{
			if (h == seam[rowsIndex])
			{
				orgHeight++;
			}
			modifiedImage.at<cv::Vec3b>(h, w) = img.at<cv::Vec3b>(orgHeight, w);
			orgHeight++;
			}

			rowsIndex--;
		    orgHeight = 0;
			}
            return modifiedImage;
			
}

cv::Mat Image ::addVerticalSeam(cv::Mat &img){

    cv:: cvtColor(img,grayScale,cv::COLOR_BGR2GRAY);
    cv::Mat eMap =calculateEnergy(grayScale);
	std::vector<int>seam=getSeamToRemove(eMap,VERTICAL);
    cv::Mat modifiedImage(img.rows, img.cols+1, CV_8UC3, cv::Scalar(0, 0, 0));
		
			int max = img.rows-1;
			int width=0;
			for (int h = 0; h < img.rows; h++)
			{
				for (int w = 0; w < img.cols; w++)
				{
					if (w == seam[max])
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
                max--;
            }
   

    return modifiedImage;
   
}

cv::Mat Image::addHorizontalSeam(cv::Mat &img){

    cv:: cvtColor(img,grayScale,cv::COLOR_BGR2GRAY);
    cv::Mat eMap =calculateEnergy(grayScale);
	std::vector<int>seam=getSeamToRemove(eMap,HORIZONTAL);
    cv::Mat modifiedImage(img.rows+1, img.cols, CV_8UC3, cv::Scalar(0, 0, 0));
			int max = width - 1;
			int height = 0;
			for (int w = 0; w < img.cols; w++)
			{
				for (int h = 0; h < img.rows; h++)
				{
					// duplicate best seam
					if (h == seam[max])
					{
						modifiedImage.at<cv::Vec3b>(h, w) = img.at<cv::Vec3b>(height, w);
                        //modifiedImage.at<cv::Vec3b>(h, w) = 255;
						modifiedImage.at<cv::Vec3b>(h+1, w) = img.at<cv::Vec3b>(height, w);
						h++;
						height++;
					}
					else
					{
						modifiedImage.at<cv::Vec3b>(h, w) = img.at<cv::Vec3b>(height, w);
						height++;
					}
				}
				height = 0;
				max--;
			}	
			
    return modifiedImage;
   

}



cv::Mat Image::seamcarve(cv::Mat& img, carveMode mode){
     cv::Mat modImg;
     switch(mode){
         case VERTICAL_TRIM:
            modImg=removeVerticalSeam(img);
            break;
        case HORIZONTAL_TRIM:
            modImg=removeHorizontalSeam(img);
            break;
        case HORIZONTAL_ADD:
            modImg=addHorizontalSeam(img);
            break;
        case  VERTICAL_ADD :
            modImg=addVerticalSeam(img);
            break;
            
     }
     return modImg;
}