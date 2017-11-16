//
//  CoinDetector.cpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/9/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//


#include "CoinDetector.h"
#include "../Transformations.h"
#include "ColorDetector.h"

void countCoins(const cv::Mat& original,
                 const std::vector<Circle>& detectedCircles) {
    
    for(Circle circle : detectedCircles) {
        
        cv::Mat mask = cv::Mat::zeros( original.rows, original.cols, CV_8UC1 );
        
        cv::circle(mask, circle.center(), circle.radius(),
                   cv::Scalar(255,255,255), 6, 8);
        
        cv::Mat result;
        
        extractShapeFromImage(original, mask, result);
        
        CustomColor paperColor = detectColor(result, 0);
        
        if (paperColor == Gold) {
            printf("Found Coin Money : 0.5 LE\n");
        }
        else if (paperColor == Silver) {
            printf("Found Coin Money : 0.25 LE\n");
        }
        else if (paperColor == SilverGold) {
            printf("Found Coin Money : 1.0 LE\n");
        }
        
    }
}

void DetectCoins(cv::Mat original,
                       const std::vector<Circle> detectedCircles) {
    
    countCoins(original, detectedCircles);
    
    for(int circle = 0; circle < detectedCircles.size(); circle++) {
        
        cv::circle(original, detectedCircles[circle].center(), detectedCircles[circle].radius(),
                   cv::Scalar(0,0,255), 6, 8);
    }
}



