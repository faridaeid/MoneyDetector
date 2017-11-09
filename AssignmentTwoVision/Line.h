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
    
public:
    
    Line(){};
    
    Line(cv::Point p1, cv::Point p2) {
        this->p1 = p1;
        this->p2 = p2;
    }
    
    void setPointOne(int x, int y) {
        p1 = cv::Point(x,y);
    }
    
    void setPointTwo(int x, int y) {
        p2 = cv::Point(x,y);
    }
    
    cv::Point pointOne() {
        return p1;
    }
    
    cv::Point pointTwo() {
        return p2;
    }

};

#endif
