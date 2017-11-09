//
//  Circle.h
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/8/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef Circle_h
#define Circle_h

#include <opencv2/core/core.hpp>

class Circle {
    
private:
    cv::Point c;
    int r;
    
public:
    Circle() {}
    Circle(int x, int y, int r) {
        c = cv::Point(x,y);
        this->r = r;
    }
    
    cv::Point center() {
        return c;
    }
    
    int radius() {
        return r;
    }
    
    void setCenter(int x, int y) {
        c = cv::Point(x,y);
    }
    
    void setRadius(int r) {
        this->r = r;
    }
    
    
    
};


#endif /* Circle_h */
