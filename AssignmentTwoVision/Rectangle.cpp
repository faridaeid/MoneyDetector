//
//  Rectangle.cpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/16/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "Rectangle.h"

void Rectangle::addCorder(cv::Point c) {
    if (corners.size() < 4) {
        corners.push_back(c);
    }
}

void Rectangle::setOrientation(int orient) {
    this->orient = orient;
}

cv::Point& Rectangle::operator[](int index) {
    return corners[index];
}

int Rectangle::orientation() {
    return orient;
}

cv::Point Rectangle::Center() {
    return cv::Point((corners[0].x + corners[2].x) / 2 ,
                     (corners[0].y + corners[2].y) / 2);
}

Rectangle Rectangle::average(const Rectangle& other) {
    
    Rectangle answer;
    
    for (int i = 0; i < corners.size(); i++){
        answer.addCorder(cv::Point( (corners[i].x + other.corners[i].x) / 2,
                                   (corners[i].y + other.corners[i].y) / 2));
    }
    
    return answer;
    
}
