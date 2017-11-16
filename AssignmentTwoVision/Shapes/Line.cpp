//
//  Line.cpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/16/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "Line.h"

Line::Line(cv::Point p1, cv::Point p2) {
    this->p1 = p1;
    this->p2 = p2;
};

cv::Point Line::pointOne() const{
    return p1;
}

cv::Point Line::pointTwo() const{
    return p2;
}

int Line::theta() const {
    return th;
}

int Line::raw() const {
    return ra;
}

void Line::setPointOne(int x, int y) {
    p1 = cv::Point(x,y);
}

void Line::setPointTwo(int x, int y) {
    p2 = cv::Point(x,y);
}

void Line::setTheta(int th) {
    this->th = th;
}

void Line::setRaw(int ra) {
    this->ra = ra;
}

cv::Point Line::getIntersection(const Line& other) const {
    
    double th1 = CV_PI * this->theta()/180.0;
    double th2 = CV_PI * other.theta()/180.0;
    
    int x, y;
    
    if (abs(this->theta() - other.theta()) == 90 && (!this->theta() || !other.theta())) {
        
        if (this->theta() != 0) {
            x = this->raw() / sin(th1);
            y = other.raw() / cos(th2);
        }
        else {
            y = this->raw() / cos(th1);
            x = other.raw() / sin(th2);
        }
    }
    else {
        
        x =  (this->raw()*cos(th2) - other.raw()*cos(th1)) / (sin(th1)*cos(th2) - sin(th2)*cos(th1));
        y = (this->raw() - x*sin(th1)) / cos(th1);
        
    }
    return cv::Point(y, x);
}
