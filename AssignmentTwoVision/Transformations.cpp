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
#include <iostream>

using namespace cv;

void floodFillPicture(const Mat& image,
                      Mat& floodFill) {
    
    floodFill = image.clone();
    
    cv::floodFill(floodFill, cv::Point(0,0), cv::Scalar(255));
    
    bitwise_not(floodFill, floodFill);
    
    floodFill = image | floodFill;
    
}

void convertToGradient(Mat& image, int threshold) {
    
    for (int i = 0; i < 5; i++) {
        blur(image, image, Size(9,9));
    }
    
    cvtColor(image, image, COLOR_BGR2GRAY);
    
    Mat gradX, gradY;
    
    Sobel(image, gradX, CV_32F, 1, 0, 3);
    Sobel(image, gradY, CV_32F, 0, 1, 3);
    
    magnitude(gradX, gradY, image);
    
    normalize(image, image, 0.0, 255.0, NORM_MINMAX, CV_8U);
    
    for (int i = 0; i < 10; i++) {
        blur(image, image, Size(7,7));
    }
    
    cv::threshold(image, image, 0, 255, THRESH_BINARY + THRESH_OTSU);

    Laplacian( image, image, CV_16S, 3, 1, 0, BORDER_DEFAULT);
    
    convertScaleAbs( image, image );
    
    for (int i = 0; i < 10; i++) {
        blur(image, image, Size(7,7));
    }
    
    cv::threshold(image, image, 0, 255, THRESH_BINARY + THRESH_OTSU);
    
    floodFillPicture(image.clone(), image);
    
    Laplacian( image, image, CV_16S, 3, 1, 0, BORDER_DEFAULT);
    
    convertScaleAbs( image, image );
    
}

void extractShapeFromImage(const cv::Mat src,
               const cv::Mat mask,
               cv::Mat& dst) {
    
    Mat maskedResult;
    
    floodFillPicture(mask, maskedResult);
    
    src.copyTo(dst, maskedResult);
}

