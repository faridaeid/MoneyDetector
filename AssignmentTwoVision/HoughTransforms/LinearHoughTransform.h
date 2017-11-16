//
//  HoughTranforms.hpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/7/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef HoughTranforms_hpp
#define HoughTranforms_hpp

#include <vector>
#include "../Shapes/Line.h"

void LinearHoughTransform(const cv::Mat& image,
                          std::vector<Line> & lines,
                          const int& threshold,
                          const int& minGap,
                          const int& showHough = 0);

#endif /* HoughTranforms_hpp */
