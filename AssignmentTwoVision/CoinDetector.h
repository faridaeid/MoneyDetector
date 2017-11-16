//
//  CoinDetector.hpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/9/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef CoinDetector_hpp
#define CoinDetector_hpp

#include "Circle.h"

void DetectCoins(cv::Mat original,
                 const std::vector<Circle> detectedCircles);

#endif /* CoinDetector_hpp */
