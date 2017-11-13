//
//  RectangleDetector.cpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/9/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "RectangleDetector.h"
#include <unordered_map>

using namespace std;

void DetectRectangle(cv::Mat original,
                     const std::vector<Line> detectedLines) {
    
    vector<vector<Line>> orderedLines (181, vector<Line>());
    
    
    for (int line = 0; line < detectedLines.size(); line++) {
        orderedLines[detectedLines[line].theta() + 90].push_back(detectedLines[line]);
    }
    
    vector<Line> rectangles;
    
    for (int theta = 0; theta < 180; theta++) {
        
        int perp = (theta < 90) ? theta + 90 : theta - 90;
        
        if (orderedLines[theta].size() > 1 && orderedLines[perp].size() > 1) {
            
            for (Line line : orderedLines[theta]) {
                
                for (int i = 0; i < orderedLines[perp].size() - 1; i+= 2) {
                    
                    Line l(line.getIntersection(orderedLines[perp][i]),
                           line.getIntersection(orderedLines[perp][i+1]));
                    
                    rectangles.push_back(l);
                }
                
            }
            
            
        }
    }
    
    for(int line = 0; line < rectangles.size(); line++) {
        
        cv::line(original, rectangles[line].pointOne(), rectangles[line].pointTwo(), cv::Scalar(255,0,0), 3, 8);

     }
}
