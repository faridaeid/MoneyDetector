//
//  RectangleDetector.cpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/9/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "RectangleDetector.h"
#include "../Transformations.h"
#include "../Shapes/Rectangle.h"
#include "ColorDetector.h"
#include <unordered_map>

using namespace std;


void GenerateRectange(const vector<vector<Line>>& orderedLines,
                      vector<Rectangle>& rectangles) {
    
    for (int theta = 0; theta < 90; theta++) {
        
        int perp = (theta < 90) ? theta + 90 : theta - 90;
        
        if (orderedLines[theta].size() > 1 && orderedLines[perp].size() > 1) {
            
            for (int line1 = 0; line1 < orderedLines[theta].size() - 1; line1++) {
                
                for (int line2 = line1 + 1; line2 < orderedLines[theta].size(); line2++) {
                    
                    Rectangle rect;
                    int orien = (theta < 90) ? theta : theta - 90;
                    rect.setOrientation(orien);
                    
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
}

void removeCloseRectangles(vector<Rectangle> & rectangles) {
    
    vector<Rectangle> finalRect;
    vector<bool> drawn(rectangles.size(), false);
    
    for (int i = 0; i < rectangles.size(); i++) {
        
        cv::Point p1 = rectangles[i].Center();
        int j;
        
        for (j = i+1; j < rectangles.size(); j++) {
            
            cv::Point p2 = rectangles[j].Center();

            if (abs(p1.x - p2.x) < 20
                && abs(p1.y - p2.y) < 20
                && abs(rectangles[i].orientation() - rectangles[j].orientation()) < 5) {
                
                finalRect.push_back(rectangles[i]);
                drawn[j] = true;
                break;
                
            }
        }
        
        if (j >= rectangles.size() && !drawn[i]) {
            finalRect.push_back(rectangles[i]);
            drawn[i] = true;
        }
    }
    
    rectangles.clear();
    rectangles.resize(0);
    
    for (Rectangle r : finalRect) {
        rectangles.push_back(r);
    }
}

void countPapers(const cv::Mat& original,
                 vector<Rectangle>& rectangles) {
    
        for(Rectangle rect : rectangles) {
        
            cv::Mat mask = cv::Mat::zeros( original.rows, original.cols, CV_8UC1 );
        
            for (int i = 0; i < 4; i++) {
            
                cv::line(mask, rect[i], rect[(i+1)%4], cv::Scalar(255,255,255), 3, 8);
            }
        
            cv::Mat result;
        
            extractShapeFromImage(original, mask, result);
            
            CustomColor paperColor = detectColor(result, 1);
            
            if (paperColor == Redish) {
                printf("Found Paper Money : 200 LE\n");
            }
            else if (paperColor == White) {
                printf("Found Paper Money : 100 LE\n");
            }
        }
}


void DetectRectangle(cv::Mat original,
                     const std::vector<Line> detectedLines) {
    
    vector<vector<Line>> orderedLines (181, vector<Line>());
    
    
    for (int line = 0; line < detectedLines.size(); line++) {
        orderedLines[detectedLines[line].theta() + 90].push_back(detectedLines[line]);
    }
    
    vector<Rectangle> rectangles;
    
    GenerateRectange(orderedLines, rectangles);
    
    removeCloseRectangles(rectangles);
    
    countPapers(original, rectangles);
    
    for(Rectangle rect : rectangles) {
        
        for (int i = 0; i < 4; i++) {
        
            cv::line(original, rect[i], rect[(i+1)%4], cv::Scalar(255,0,0), 3, 8);
            
        }

     }
}

