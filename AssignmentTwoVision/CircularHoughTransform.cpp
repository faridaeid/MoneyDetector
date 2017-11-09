//
//  CircularHoughTransform.cpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/8/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "CircularHoughTransform.h"
#include "Matrix.h"
#include "Circle.h"
#include <vector>

using namespace std;
using namespace cv;

void fillCircularAccumelator(const Mat& image,
                             vector<Matrix<int>>& accumelator,
                             int minRad,
                             int step) {
    
    int xc, yc;
    
    for (int y = 0; y < image.rows; y++) {
        
        for (int x = 0; x < image.cols; x++) {
            
            if (image.at<uchar>(y,x) > 50) {
            
                for (int r = 0; r < accumelator.size(); r++) {
                    
                    int radius = minRad + r*step;
                    
                    for (int theta = 0; theta < 360; theta++) {
                        
                        double thetaRad = CV_PI * theta/360.0;
                        
                        xc = x + radius*cos(thetaRad);
                        yc = y + radius*sin(thetaRad);
                        
                        if (xc < 0 || xc >= image.cols || yc < 0 || yc >= image.rows) {
                            continue;
                        }
                        
                        accumelator[r][yc][xc]++;
                        
                    }
                }
            }
        }
    }
}

vector<Circle> getDetectedCircle(const vector<Matrix<int>>& accumelator,
                                 int threshold,
                                 int minRad,
                                 int step) {
    
    vector<Circle> detected;
    Circle circle;
    
    for (int r = 0; r < accumelator.size(); r++) {
        
        for (int y = 0; y < accumelator[r].rows(); y++) {
            
            for (int x = 0; x < accumelator[r].cols(); x++) {
                
                if (accumelator[r][y][x] >= threshold) {
                    circle.setRadius(minRad + step*r);
                    circle.setCenter(x, y);
                    detected.push_back(circle);
                }
            }
        }
    }
    
    return detected;
}


void getCirclesHoughTransform(cv::Mat& originalImage,
                              cv::Mat& image ,
                              int minRad,
                              int maxRad,
                              int step,
                              const int& showHough) {
    
    string windowName = "Sample Circular Hough Space";
    
    int size = (maxRad - minRad)/step + 1;
    vector<Matrix<int>> accumelator(size, Matrix<int>(image.rows,image.cols));
    
    fillCircularAccumelator(image, accumelator, minRad, step);
    vector<Circle> circles = getDetectedCircle(accumelator, 150, minRad, step);
    
    for(int circle = 0; circle < circles.size(); circle++) {
        
        cv::circle(originalImage, circles[circle].center(), circles[circle].radius(),
                   Scalar(0,0,255), 3, 8);
        
    }
    
    Mat hough = Mat(accumelator[0].rows(), accumelator[0].cols(), CV_8UC1, Scalar(255, 255, 255));
    
    for (int y = 0; y < hough.rows; y++) {
        for (int x = 0; x < hough.cols; x++) {
            
            hough.at<uchar>(y,x) = 255 - accumelator[0][y][x];
            
        }
    }
    
    if (showHough) {
        namedWindow(windowName, WINDOW_NORMAL);
        imshow(windowName, hough);
    }

    
    
}
