//
//  main.cpp
//  Ch2
//
//  Created by zz on 8/16/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;

void ex2_1() {
    cv::Mat img = cv::imread("./assets/img/zju.png", -1);
    if (img.empty()) return;
    cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example1", img);
    cv::waitKey(0);
    cv::destroyWindow("Example1");
}

void ex2_2() {
    Mat img = imread("./assets/img/zju.png", -1);
    if (img.empty()) return;
    namedWindow("Example1", WINDOW_AUTOSIZE);
    imshow("Example1", img);
    waitKey(0);
    destroyWindow("Example1");
}

int main(int argc, const char* argv[]) {
    ex2_2();
    return 0;
}
