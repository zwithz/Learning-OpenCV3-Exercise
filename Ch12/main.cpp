//
//  main.cpp
//  Ch12
//
//  Created by zz on 9/13/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

/**
 * Example 12-1
 * Using cv::dfs() and cv::idft to accelerate the computation
 * of convoluitons
 */
void ex1() {
    Mat A = imread("../assets/img/zju.png", 0);
    if (A.empty()) return;

    Size pathSize(100, 100);
    Point topLeft(A.cols / 2, A.rows / 2);
    Rect roi(topLeft.x, topLeft.y, pathSize.width, pathSize.height);

    Mat B = A(roi);

    int dft_M = getOptimalDFTSize(A.rows + B.rows - 1);
    int dft_N = getOptimalDFTSize(A.cols + B.cols - 1);

    Mat dft_A = Mat::zeros(dft_M, dft_N, CV_32F);
    Mat dft_B = Mat::zeros(dft_M, dft_N, CV_32F);

    Mat dft_A_part = dft_A(Rect(0, 0, A.cols, A.rows));
    Mat dft_B_part = dft_B(Rect(0, 0, B.cols, B.rows));

    A.convertTo(dft_A, dft_A.type(), 1, -mean(A)[0]);
    B.convertTo(dft_B, dft_B.type(), 1, -mean(B)[0]);

    dft(dft_A, dft_A, 0, A.rows);
    dft(dft_B, dft_B, 0, B.rows);

    // Set the last parameter to false to compute convolution
    // instead of correlation
    mulSpectrums(dft_A, dft_B, dft_A, 0, true);
    idft(dft_A, dft_A, DFT_SCALE, A.rows + B.rows - 1);

    Mat corr = dft_A(Rect(0, 0, A.cols + B.cols - 1, A.rows + B.rows - 1));
    normalize(corr, corr, 0, 1, NORM_MINMAX, corr.type());
    pow(corr, 3., corr);

    B ^= Scalar::all(255);

    imshow("Image", A);
    imshow("Correlation", corr);
    waitKey(0);
}

int main(int argc, const char* argv[]) {
    ex1();
    return 0;
}
