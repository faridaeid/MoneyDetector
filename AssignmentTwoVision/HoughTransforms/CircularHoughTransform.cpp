//
//  CircularHoughTransform.cpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/8/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "CircularHoughTransform.h"
#include "Matrix.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;
using namespace cv;

struct QueueObject {
    
    int thresh;
    Circle c;
    
    bool operator < (const QueueObject& rhs) const {
        return rhs.thresh > thresh;
    }
};

void fillCircularAccumelator(const Mat& image,
                             vector<Circle>& detectedCircles,
                             vector<Matrix<int>>& accumelator,
                             const int& threshold,
                             const int& minRad,
                             const int& step) {
    
    int xc, yc, vote;
    Circle circle;
    
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
                        
                        vote = ++accumelator[r][yc][xc];
                        
                        if (vote == threshold) {
                            
                            circle.setRadius(r);
                            circle.setCenter(xc, yc);
                            detectedCircles.push_back(circle);
                            
                        }
                        
                    }
                }
            }
        }
    }
}

void removeCloseCircles(std::vector<Circle>& detectedCircles,
                        vector<Matrix<int>>& accumelator,
                        const int& minGap) {
    
    priority_queue<QueueObject> queue;
    Circle curr;
    QueueObject queueObject;
    
    for (Circle c : detectedCircles) {
        queueObject.thresh = accumelator[c.radius()][c.center().y][c.center().x];
        queueObject.c = c;
        queue.push(queueObject);
    }
    
    detectedCircles.clear();
    detectedCircles.resize(0);
    
    while (!queue.empty()) {
        
        curr = queue.top().c;
        queue.pop();
        
        if (accumelator[curr.radius()][curr.center().y][curr.center().x]) {
            detectedCircles.push_back(curr);
            
            for (int r = 0; r < accumelator.size(); r++) {
            
                for(int i = -minGap; i <= minGap; i++) {
                    for (int j = -minGap; j <= minGap; j++) {
                        accumelator[r][curr.center().y + j][curr.center().x + i] = 0;
                    }
                }
            }
        }
        
    }
}

void getCirclesHoughTransform(const cv::Mat& image ,
                              std::vector<Circle>& detectedCircles,
                              const int& threshold,
                              const int& minRad,
                              const int& maxRad,
                              const int& step,
                              const int& minGap,
                              const int& showHough) {
    
    int size = (maxRad - minRad)/step + 1;
    
    vector<Matrix<int>> accumelator(size, Matrix<int>(image.rows,image.cols));
    
    fillCircularAccumelator(image, detectedCircles, accumelator, threshold, minRad, step);
    
    removeCloseCircles(detectedCircles, accumelator, minGap);
    
    for(int i = 0; i < detectedCircles.size(); i++) {
        detectedCircles[i].setRadius(minRad + step* detectedCircles[i].radius());
    }
    
    if (showHough) {
        
        Mat hough = Mat(accumelator[0].rows(), accumelator[0].cols(), CV_8UC1, Scalar(255, 255, 255));
        
        for (int y = 0; y < hough.rows; y++) {
            for (int x = 0; x < hough.cols; x++) {
                
                hough.at<uchar>(y,x) = 255 - accumelator[0][y][x];
                
            }
        }
        
        string windowName = "Sample Circular Hough Space";

        namedWindow(windowName, WINDOW_NORMAL);
        imshow(windowName, hough);
    }

    
    
}
