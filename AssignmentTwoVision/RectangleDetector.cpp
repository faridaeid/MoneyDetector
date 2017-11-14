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

struct Rectangle {
    
    vector<cv::Point> corners;
    
    void addCorder(cv::Point c) {
        if (corners.size() < 4) {
            corners.push_back(c);
        }
    }
    
    cv::Point& operator[](int index) {
        return corners[index];
    }
};

void DetectRectangle(cv::Mat original,
                     const std::vector<Line> detectedLines) {
    
    vector<vector<Line>> orderedLines (181, vector<Line>());
    
    
    for (int line = 0; line < detectedLines.size(); line++) {
        orderedLines[detectedLines[line].theta() + 90].push_back(detectedLines[line]);
    }
    
    vector<Rectangle> rectangles;
    
    for (int theta = 0; theta < 180; theta++) {
        
        int perp = (theta < 90) ? theta + 90 : theta - 90;
        
        if (orderedLines[theta].size() > 1 && orderedLines[perp].size() > 1) {
            
            for (int line1 = 0; line1 < orderedLines[theta].size() - 1; line1++) {
                
                for (int line2 = line1 + 1; line2 < orderedLines[theta].size(); line2++) {
                    
                    Rectangle rect;
                
                    for (int line3 = 0; line3 < orderedLines[perp].size() - 1; line3++) {
                        
                        rect.addCorder(orderedLines[theta][line1].getIntersection(orderedLines[perp][line3]));
                        rect.addCorder(orderedLines[theta][line2].getIntersection(orderedLines[perp][line3]));

                        for (int line4 = line3 + 1; line4 < orderedLines[perp].size(); line4++) {
                    
                            rect.addCorder(orderedLines[theta][line2].getIntersection(orderedLines[perp][line4]));
                            rect.addCorder(orderedLines[theta][line1].getIntersection(orderedLines[perp][line4]));
                            
                            rectangles.push_back(rect);
                    
                        }
                    }
                }
            }
        }
    }


    for(Rectangle rect : rectangles) {
        
        for (int i = 0; i < 4; i++) {
        
            cv::line(original, rect[i], rect[(i+1)%4], cv::Scalar(255,0,0), 3, 8);
            
        }

     }
}
