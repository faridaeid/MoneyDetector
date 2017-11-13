//
//  Line.cpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/7/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef LINE_H
#define LINE_H

#include <opencv2/core/core.hpp>


class Line {
    
private:
    
    cv::Point p1;
    cv::Point p2;
    int th;
    int ra;
    
public:
    
    Line(){};
    
    Line(cv::Point p1, cv::Point p2) {
        this->p1 = p1;
        this->p2 = p2;
    }
    
    cv::Point pointOne() const{
        return p1;
    }
    
    cv::Point pointTwo() const{
        return p2;
    }
    
    int theta() const {
        return th;
    }
    
    int raw() const {
        return ra;
    }
    
    void setPointOne(int x, int y) {
        p1 = cv::Point(x,y);
    }
    
    void setPointTwo(int x, int y) {
        p2 = cv::Point(x,y);
    }
    
    void setTheta(int th) {
        this->th = th;
    }
    
    void setRaw(int ra) {
        this->ra = ra;
    }
    
    cv::Point getIntersection(const Line& other) {
        
        double th1 = CV_PI * this->theta()/180.0;
        double th2 = CV_PI * other.theta()/180.0;

        int x =  (this->raw()*cos(th2) - other.raw()*cos(th1)) / (sin(th1)*cos(th2) - sin(th2)*cos(th1));
        
        int y = (this->raw() - x*sin(th1)) / cos(th1);
        
        return cv::Point(y, x);
    }

};

#endif
