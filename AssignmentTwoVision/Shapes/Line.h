//
//  Line.cpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/7/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef LINE_H
#define LINE_H

#include <opencv2/opencv.hpp>

class Line {
    
private:
    
    cv::Point p1;
    cv::Point p2;
    int th;
    int ra;
    
public:
    
    Line(){};
    
    Line(cv::Point p1, cv::Point p2);
    cv::Point pointOne() const;
    cv::Point pointTwo() const;
    int theta() const;
    int raw() const;
    void setPointOne(int x, int y);
    void setPointTwo(int x, int y);
    void setTheta(int th);
    void setRaw(int ra);
    cv::Point getIntersection(const Line& other) const;

};

#endif
