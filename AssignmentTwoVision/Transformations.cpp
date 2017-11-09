//
//  Transformations.cpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/7/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "Transformations.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

void convertToGradient(Mat& image, int threshold) {
    
    //(image, image, COLOR_BGR2GRAY);
    //blur(image, image, Size(5,5));
    GaussianBlur(image, image, Size(11,11), 0, 0, BORDER_DEFAULT);
    Canny(image, image, threshold/3, threshold, 3);
    
    
    /*GaussianBlur(image, image, Size(3,3), 0, 0, BORDER_DEFAULT);
    
    cvtColor(image, image, COLOR_BGR2GRAY);
    
    Mat gradX, gradY;
    
    Sobel(image, gradX, CV_32F, 1, 0, 3);
    Sobel(image, gradY, CV_32F, 0, 1, 3);
    
    magnitude(gradX, gradY, image);
    
    normalize(image, image, 0.0, 255.0, NORM_MINMAX, CV_8U);*/
    
}
