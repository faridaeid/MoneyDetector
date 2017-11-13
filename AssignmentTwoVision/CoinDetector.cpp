//
//  CoinDetector.cpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/9/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "CoinDetector.h"


void DetectCoins(cv::Mat original,
                       const std::vector<Circle> detectedCircles) {
    
    for(int circle = 0; circle < detectedCircles.size(); circle++) {
        
        cv::circle(original, detectedCircles[circle].center(), detectedCircles[circle].radius(),
                   cv::Scalar(0,0,255), 3, 8);
    }
}
