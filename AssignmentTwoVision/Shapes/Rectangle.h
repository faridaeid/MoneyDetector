//
//  Rectangle.hpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/16/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef Rectangle_hpp
#define Rectangle_hpp

#include <opencv2/opencv.hpp>

class Rectangle {
    
private:
    
    std::vector<cv::Point> corners;
    int orient;
    
public:
    
    Rectangle(){};
    void addCorder(cv::Point c);
    void setOrientation(int orient);
    cv::Point& operator[](int index);
    int orientation();
    cv::Point Center();
    Rectangle average(const Rectangle& other);
};


#endif /* Rectangle_hpp */
