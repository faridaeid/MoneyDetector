//
//  CircularHoughTransform.hpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/8/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef CircularHoughTransform_hpp
#define CircularHoughTransform_hpp

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


void getCirclesHoughTransform(cv::Mat& originalImage,
                              cv::Mat& image ,
                              int minRad,
                              int maxRad,
                              int step,
                              const int& showHough = 0);

#endif /* CircularHoughTransform_hpp */
