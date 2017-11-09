//
//  RectangleDetector.cpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/9/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "RectangleDetector.h"

void RectangleDetector(cv::Mat original,
                       const std::vector<Line> detectedLines) {
    
    for(int line = 0; line < detectedLines.size(); line++) {
     
        cv::line(original, detectedLines[line].pointOne(), detectedLines[line].pointTwo(), cv::Scalar(0,0,255), 2, 8);
     
     }
}
