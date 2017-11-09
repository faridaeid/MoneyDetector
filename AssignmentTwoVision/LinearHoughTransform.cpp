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


void getLinesHoughTransform(Mat& originalImage ,
                            Mat& edgeDetImage,
                            int threshold,
                            const int& showHough) {
    
    int range = sqrt(2)*max(edgeDetImage.cols, edgeDetImage.rows) * 2;
    
    Matrix<int> accumelator(range + 1, 181);
    
    vector<Polar> highVotePolar;
    
    fillLinearAccumelator(edgeDetImage, accumelator, threshold, highVotePolar);
    
    vector<Line> lines = getDetectedLines(highVotePolar, edgeDetImage.cols, edgeDetImage.rows);
    
    for(int line = 0; line < lines.size(); line++) {
        
        cv::line(originalImage, lines[line].pointOne(), lines[line].pointTwo(), Scalar(0,0,255), 2, 8);
        
    }
    
    
    Mat hough = Mat(accumelator.rows(), accumelator.cols(), CV_8UC1, Scalar(255, 255, 255));
    
    for (int y = 0; y < hough.rows; y++) {
        for (int x = 0; x < hough.cols; x++) {
            
            hough.at<uchar>(y,x) = 255 - accumelator[y][x];
            
        }
    }
    
    if (showHough) {
        namedWindow("what", WINDOW_NORMAL);
        imshow("what", hough);
    }
}

/*vector<Line> getDetectedLines(const Matrix<int>& accumelator,
                              int threshold,
                              int mid,
                              int imageWidth,
                              int imageHeight) {
    
    vector<Line> detected;
    Line line;
    
    for (int r = 0; r < accumelator.rows(); r++) {
        
        int realr = r - mid;
        
        for (int theta = -90; theta <= 90; theta++) {
            
            if (accumelator[r][theta + 90] >= threshold) {
                
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
        }
    }
    
    return detected;
}


void getLinesHoughTransform(Mat& originalImage ,
                            Mat& edgeDetImage,
                            const int& threshold,
                            const int& showHough) {
    
    int range = sqrt(2)*max(edgeDetImage.cols, edgeDetImage.rows) * 2;
    
    Matrix<int> accumelator(range + 1, 181);
    
    fillLinearAccumelator(edgeDetImage, accumelator);
    
    vector<Line> lines = getDetectedLines(accumelator, 190, range/2, edgeDetImage.cols, edgeDetImage.rows);
    
    for(int line = 0; line < lines.size(); line++) {
        
        cv::line(originalImage, lines[line].pointOne(), lines[line].pointTwo(), Scalar(0,0,255), 2, 8);
        
    }
    
    
    Mat hough = Mat(accumelator.rows(), accumelator.cols(), CV_8UC1, Scalar(255, 255, 255));
    
    for (int y = 0; y < hough.rows; y++) {
        for (int x = 0; x < hough.cols; x++) {
            
            hough.at<uchar>(y,x) = 255 - accumelator[y][x];
            
        }
    }
    
    if (showHough) {
        namedWindow("what", WINDOW_NORMAL);
        imshow("what", hough);
    }
}*/
