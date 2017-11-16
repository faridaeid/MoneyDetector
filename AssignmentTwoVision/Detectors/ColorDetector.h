//
//  ColorDetector.hpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/15/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef ColorDetector_hpp
#define ColorDetector_hpp

enum CustomColor{
    Redish,
    White,
    Silver,
    SilverGold,
    Gold
};

#include <opencv2/opencv.hpp>

CustomColor detectColor(const cv::Mat& maskedImage, const int& target);

#endif /* ColorDetector_hpp */
