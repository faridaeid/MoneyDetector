//
//  Transformations.hpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/7/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef Transformations_h
#define Transformations_h

#include <opencv2/core/core.hpp>

void convertToGradient(cv::Mat& image, int thresh);

void extractShapeFromImage(const cv::Mat src,
               const cv::Mat mask,
               cv::Mat& dst);

#endif /* Transformations_hpp */
