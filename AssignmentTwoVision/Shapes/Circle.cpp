//
//  Circle.cpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/16/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "Circle.h"

Circle::Circle(int x, int y, int r) {
    c = cv::Point(x,y);
    this->r = r;
}

cv::Point Circle::center() const {
    return c;
}

int Circle::radius() const {
    return r;
}

void Circle::setCenter(int x, int y) {
    c = cv::Point(x,y);
}

void Circle::setRadius(int r) {
    this->r = r;
}
