//
//  main.cpp
//  AssignmentTwoVision
//
//  Created by Farida Eid on 11/3/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include <iostream>
#include "Transformations.h"
#include "LinearHoughTransform.h"
#include "CircularHoughTransform.h"
#include "RectangleDetector.h"
#include "CoinDetector.h"

using namespace cv;

int main(int argc, char** argv) {
    
    if (argc < 2) {
        std::cerr<<"Please Enter the Image path";
        return -1;
    }
    
    Mat image = imread(argv[1], IMREAD_COLOR);
    Mat original = image.clone();
    
    string windowName = "Output Image";
    
    
    int thresh = 40;
    vector<Line> detectedLines;
    vector<Circle> detectedCircles;
        
    convertToGradient(image, thresh);
    LinearHoughTransform(image, detectedLines, 230, 30, 1);
    DetectRectangle(original, detectedLines);
    
    getCirclesHoughTransform(image, detectedCircles, 139, 100, 150, 5, 40, 1);
    DetectCoins(original, detectedCircles);
    
    namedWindow(windowName, WINDOW_NORMAL);
    imshow(windowName, image);
    namedWindow("original", WINDOW_NORMAL);
    imshow("original", original);
    waitKey(0);
        
}
