//
//  HoughTranforms.cpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/7/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//a

#include "LinearHoughTransform.h"
#include <iostream>
#include "Matrix.h"

struct Polar {
    int raw;
    int theta;
    
    Polar(int r, int t) {
        raw = r;
        theta = t;
    }
};


using namespace std;
using namespace cv;

void fillLinearAccumelator(const Mat& image,
                           Matrix<int>& accumelator,
                           const int& threshold,
                           vector<Polar>& highVotePolar) {
    
    int mid = accumelator.rows()/2;
    int vote;
    
    for (int y = 0; y < image.rows; y++) {
        
        for (int x = 0; x < image.cols; x++) {
            
            if (image.at<uchar>(y,x) > 50) {
                
                for (int thetaDeg = -90; thetaDeg <= 90; thetaDeg++) {
                    
                    double thetaRad = CV_PI * thetaDeg/180.0;
                    
                    int raw = (x)*cos(thetaRad) + (y)*sin(thetaRad);
                    
                    vote = ++accumelator[raw + mid][thetaDeg + 90];
                    
                    if (vote == threshold) {
                        highVotePolar.push_back(Polar(raw, thetaDeg));
                    }
                }
            }
        }
    }
}

vector<Line> getDetectedLines(vector<Polar>& highVotePolar,
                              int imageWidth,
                              int imageHeight) {
    
    vector<Line> detected;
    Line line;
    
    for (Polar coord : highVotePolar) {
        
        int realr = coord.raw;
        int theta = coord.theta;
        
        double thetaRadians = CV_PI * theta/180.0;
        
        // angles between 45 - 135 caluclate the y values and the x values are at the edges
        
        if (theta > 45 || theta < -45) {
            
            int y1 = realr / sin(thetaRadians);
            line.setPointOne(0, y1);
            
            int y2 = (realr - imageWidth*cos(thetaRadians)) / sin(thetaRadians);
            line.setPointTwo(imageWidth, y2);
            
            
        } else {
            
            int x1 = realr / cos(thetaRadians);
            line.setPointOne(x1, 0);
            
            int x2 = (realr - imageHeight*sin(thetaRadians)) / cos(thetaRadians);
            line.setPointTwo(x2, imageHeight);
            
        }
        
        detected.push_back(line);
    }
    return detected;
}


void LinearHoughTransform(const cv::Mat& image,
                            std::vector<Line> & lines,
                            int threshold,
                            const int& showHough) {
    
    string windowName = "Linear Hough Space";
    
    int range = sqrt(2)*max(image.cols, image.rows) * 2;
    
    Matrix<int> accumelator(range + 1, 181);
    
    vector<Polar> highVotePolar;
    
    fillLinearAccumelator(image, accumelator, threshold, highVotePolar);
    
    lines = getDetectedLines(highVotePolar, image.cols, image.rows);
    
    Mat hough = Mat(accumelator.rows(), accumelator.cols(), CV_8UC1, Scalar(255, 255, 255));
    
    for (int y = 0; y < hough.rows; y++) {
        for (int x = 0; x < hough.cols; x++) {
            
            hough.at<uchar>(y,x) = 255 - accumelator[y][x];
            
        }
    }
    
    if (showHough) {
        namedWindow(windowName, WINDOW_NORMAL);
        imshow(windowName, hough);
    }
}
