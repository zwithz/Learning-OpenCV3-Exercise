//
//  main.cpp
//  Ch10
//
//  Created by zz on 8/26/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

/**
 * Example 10-1
 * Using cv::threshold() to sum three channels of an image
 */
void sum_rgb(const Mat& src, Mat& dst) {
    // Split image onto the color planes.
    vector<Mat> planes;
    split(src, planes);
    
    Mat b = planes[0], g = planes[1], r = planes[2], s;
    
    // Add equally weighted rgb values.
    addWeighted(r, 1./3., g, 1./3., 0.0, s);
    addWeighted(s, 1., b, 1./3., 0.0, s);
    
    // Truncate values above 100.
    threshold(s, dst, 100, 100, THRESH_TRUNC);
}

void ex1() {
    Mat src = imread("../assets/img/daxiong.png"), dst;
    if (src.empty()) return;
    sum_rgb(src, dst);
    
    namedWindow("Example1", WINDOW_AUTOSIZE);
    imshow("Example1", dst);
    
    waitKey(0);
}

/**
 * Example 10-2
 * Alternative method to combine and threshold image planes
 */
void sum_rgb2(const Mat& src, Mat& dst) {
    // Split image onto the color planes.
    vector<Mat> planes;
    split(src, planes);
    
    Mat b = planes[0], g = planes[1], r = planes[2];
    
    // Accumulate separate planes, combine and threshold.
    Mat s = Mat::zeros(b.size(), CV_32F);
    accumulate(b, s);
    accumulate(g, s);
    accumulate(r, s);
    
    // Truncate values above 100 and rescale into dst.
    threshold(s, s, 100, 100, THRESH_TRUNC);
    s.convertTo(dst, b.type());
}

void ex2() {
    Mat src = imread("../assets/img/daxiong.png"), dst;
    if (src.empty()) return;
    sum_rgb2(src, dst);
    
    namedWindow("Example1", WINDOW_AUTOSIZE);
    imshow("Example1", dst);
    
    waitKey(0);
}

/**
 * Example 10-3
 * Threshold versus adaptive threshold
 */
void ex3() {
    double fixed_threshold = 15.0;
    int threshold_type = THRESH_BINARY;
    int adaptive_method = ADAPTIVE_THRESH_MEAN_C;
    int block_size = 71;
    double offset = 15.0;
    Mat Igray = imread("../assets/img/ChongQing1.png", IMREAD_GRAYSCALE);
    
    // Read in gray image.
    if(Igray.empty()) return;
    
    // Declare the output images.
    Mat It, Iat;
    
    // Thresholds.
    threshold(Igray, It, fixed_threshold, 255, threshold_type);
    adaptiveThreshold(Igray, Iat, 255, adaptive_method, threshold_type, block_size, offset);
    
    imshow("Row", Igray);
    imshow("Threshold", It);
    imshow("Adaptive Threshold", Iat);
    waitKey(0);
}

int main(int argc, const char * argv[]) {
    ex3();
    return 0;
}
