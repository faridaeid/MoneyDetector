//
//  HoughTranforms.hpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/7/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef HoughTranforms_hpp
#define HoughTranforms_hpp

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include "Line.h"

void getLinesHoughTransform(cv::Mat& original,
                            cv::Mat& image,
                            int threshold,
                            const int& showHough = 0);

/*void getLinesHoughTransform(const cv::Mat& image,
                            std::vector<Line> & lines,
                            int threshold,
                            const int& showHough = 0);*/

#endif /* HoughTranforms_hpp */
