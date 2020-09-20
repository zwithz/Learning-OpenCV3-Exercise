//
//  main.cpp
//  Ch13
//
//  Created by zz on 9/20/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

/**
 * Example 13-1
 * Histogram computation and display
 */
void ex1() {
    Mat src = imread("../assets/img/daxiong.png");
    if (src.empty()) return;

    // Compute the HSV image, and decompose it into separate planes.
    Mat hsv;
    cvtColor(src, hsv, COLOR_BGR2HSV);

    float h_ranges[] = {0, 180};  // hue is [0, 180]
    float s_ranges[] = {0, 256};
    const float* ranges[] = {h_ranges, s_ranges};
    int histSize[] = {30, 32}, ch[] = {0, 1};

    Mat hist;

    // Compute the histogram
    calcHist(&hsv, 1, ch, noArray(), hist, 2, histSize, ranges);
    normalize(hist, hist, 0, 255, NORM_MINMAX);

    int scale = 10;
    Mat hist_img(histSize[0] * scale, histSize[1] * scale, CV_8UC3);

    // Draw our histogram
    for (int h = 0; h < histSize[0]; h++) {
        for (int s = 0; s < histSize[1]; s++) {
            float hval = hist.at<float>(h, s);
            rectangle(hist_img, Rect(h * scale, s * scale, scale, scale), Scalar::all(hval), -1);
        }
    }

    imshow("image", src);
    imshow("H-S histogram", hist_img);
    waitKey(0);
}

int main(int argc, const char* argv[]) {
    ex1();
    return 0;
}
