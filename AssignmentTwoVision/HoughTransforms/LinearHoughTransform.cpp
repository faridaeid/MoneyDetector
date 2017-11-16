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
#include <queue>

class Polar {
public:
    
    int raw;
    int theta;
    
    Polar(){};
    
    Polar(int r, int t) {
        raw = r;
        theta = t;
    }
};

struct QuObject {
    
    int thresh;
    Polar p;
        
    bool operator < (const QuObject& rhs) const {
        return rhs.thresh > thresh;
    }
};


using namespace std;
using namespace cv;

void fillLinearAccumelator(const Mat& image,
                           vector<Polar>& highVotePolar,
                           Matrix<int>& accumelator,
                           const int& threshold) {
    
    int mid = accumelator.rows()/2;
    int vote;
    
    for (int y = 0; y < image.rows; y++) {
        
        for (int x = 0; x < image.cols; x++) {
            
            if (image.at<uchar>(y,x) > 0) {
                
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

void removeCloseLines(std::vector<Polar>& detectedLines,
                      Matrix<int>& accumelator,
                      const int& minGap) {
    
    priority_queue<QuObject> queue;
    QuObject queueObject;
    int mid = accumelator.rows() / 2;
    
    for (Polar p : detectedLines) {
        queueObject.thresh = accumelator[p.raw + mid][p.theta + 90];
        queueObject.p = p;
        queue.push(queueObject);
    }
    
    detectedLines.clear();
    detectedLines.resize(0);
    
    while (!queue.empty()) {
        
        Polar curr = queue.top().p;
        queue.pop();
        
        if (accumelator[curr.raw + mid][curr.theta + 90]) {
            detectedLines.push_back(curr);
            
            int raw = curr.raw + mid;
            
            for(int i = -minGap; i <= minGap; i++) {
                if (raw + i > 0 && raw + i < accumelator.rows())
                    accumelator[raw + i][curr.theta + 90] = 0;
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
        
        line.setTheta(theta);
        line.setRaw(realr);
        detected.push_back(line);
    }
    return detected;
}


void LinearHoughTransform(const cv::Mat& image,
                          std::vector<Line> & lines,
                          const int& threshold,
                          const int& minGap,
                          const int& showHough) {
    
    int range = sqrt(2)*max(image.cols, image.rows) * 2;
    
    Matrix<int> accumelator(range + 1, 181);
    
    vector<Polar> highVotePolar;
    
    fillLinearAccumelator(image, highVotePolar, accumelator, threshold);
    
    removeCloseLines(highVotePolar, accumelator, minGap);
    
    lines = getDetectedLines(highVotePolar, image.cols, image.rows);
    
    
    if (showHough) {
        
        Mat hough = Mat(accumelator.rows(), accumelator.cols(), CV_8UC1, Scalar(255, 255, 255));
        
        for (int y = 0; y < hough.rows; y++) {
            for (int x = 0; x < hough.cols; x++) {
                
                hough.at<uchar>(y,x) = 255 - accumelator[y][x];
                
            }
        }
        
        string windowName = "Linear Hough Space";
        
        namedWindow(windowName, WINDOW_NORMAL);
        imshow(windowName, hough);
    }
}
