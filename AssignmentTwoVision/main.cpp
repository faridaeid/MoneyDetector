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

using namespace cv;

int main(int argc, char** argv) {
    
    if (argc < 2) {
        std::cerr<<"Please Enter the Image path";
        return -1;
    }
    
    Mat image = imread(argv[1], IMREAD_COLOR);
    Mat original = image;
    
    string windowName = "Output Image";
    
    
    int thresh = 60;
    vector<Line> detectedLines;
        
    convertToGradient(image, thresh);
    LinearHoughTransform(image, detectedLines, 100, 1);
    RectangleDetector(original, detectedLines);
    
    //getCirclesHoughTransform(original, image, 40, 100, 5, 1);
    
    namedWindow(windowName, WINDOW_NORMAL);
    imshow(windowName, original);
    waitKey(0);
        
}
