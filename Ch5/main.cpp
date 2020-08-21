//
//  main.cpp
//  Ch5
//
//  Created by zz on 8/20/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
using namespace std;

/**
 * Example 5-1. Complete program to alpha-blend the ROI starting at (0, 0)
 * in src2 with the ROI starting at (x, y) in src1
 */
void ex1(int x, int y, int w, int h, double alpha, double beta) {
    Mat src1 = imread("", 1);
    Mat src2 = imread("", 1);
    
    if(!src1.empty() && !src2.empty()) {
        Mat roi1(src1, Rect(x, y, w, h));
        Mat roi2(src2, Rect(0, 0, w, h));
        
        addWeighted(roi1, alpha, roi2, beta, 0.0, roi1);
        
        namedWindow("Alpha Blend", WINDOW_AUTOSIZE);
        imshow("Alpha Blend", src1);
        waitKey(0);
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
