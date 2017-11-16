//
//  Circle.h
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/8/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef Circle_h
#define Circle_h

#include <opencv2/opencv.hpp>

class Circle {
    
private:
    cv::Point c;
    int r;
    
public:
    Circle() {}
    Circle(int x, int y, int r);
    cv::Point center() const;
    int radius() const;
    void setCenter(int x, int y);
    void setRadius(int r);
};


#endif /* Circle_h */
