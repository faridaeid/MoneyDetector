//
//  CircularHoughTransform.hpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/8/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef CircularHoughTransform_hpp
#define CircularHoughTransform_hpp

#include "Circle.h"

void getCirclesHoughTransform(const cv::Mat& image ,
                              std::vector<Circle>& detectedCircles,
                              const int& threshold,
                              const int& minRad,
                              const int& maxRad,
                              const int& step,
                              const int& minGap = 5,
                              const int& showHough = 0);

#endif /* CircularHoughTransform_hpp */
