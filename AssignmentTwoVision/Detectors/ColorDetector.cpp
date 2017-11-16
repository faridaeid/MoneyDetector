//
//  ColorDetector.cpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/15/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "ColorDetector.h"


CustomColor detectColor(const cv::Mat& maskedImage, const int& target) {
    
    CustomColor customColors[] = {Redish, White, Gold, Silver, SilverGold};
    
    std::pair<cv::Scalar, cv::Scalar> boundaries[] = {
        std::make_pair(cv::Scalar(130, 205, 210), cv::Scalar(190, 255, 255)),
        std::make_pair(cv::Scalar(70, 30 , 60), cv::Scalar(140, 160, 170)),
        std::make_pair(cv::Scalar(80,140,180), cv::Scalar(130,170,210)),
        std::make_pair(cv::Scalar(170,200,200), cv::Scalar(200,245,255))};
    
    double max = 0;
    double ratio[4];
    CustomColor maxColor;
    
    int end = (target == 1) ? 2 : 4;
    int start = (target == 1) ? 0 : 2;
    
    for (int i = start; i < end; i++) {
        
        cv::Mat greyImage;
        
        cv::cvtColor(maskedImage, greyImage, CV_RGB2GRAY);
        
        cv::threshold(greyImage, greyImage, 0, 255.0, cv::THRESH_BINARY);
    
        int maskSize = cv::countNonZero(greyImage);
    
        cv::Mat Mask;
    
        cv::inRange(maskedImage, boundaries[i].first , boundaries[i].second, Mask);
        
        int colorSize = cv::countNonZero(Mask);
    
        ratio[i] = double(colorSize)/double(maskSize);
        
        if (ratio[i] > max) {
            max = ratio[i];
            maxColor = customColors[i];
        }
    }
    
    if (ratio[3] > 0.05 && ratio[2] > 0.05 && target == 0) {
        maxColor = customColors[4];
    }

    return maxColor;
}
