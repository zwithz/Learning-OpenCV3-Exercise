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

/**
 * Example 12-2
 * Using cv::HoughCircles() to return a sequence of circles
 * found in a grayscale image
 */
void ex2() {
    Mat src, image;
    src = imread("../assets/img/zju.png", 1);
    if (src.empty()) return;

    cvtColor(src, image, COLOR_BGR2GRAY);
    GaussianBlur(image, image, Size(5, 5), 0, 0);

    vector<Vec3f> circles;
    HoughCircles(image, circles, HOUGH_GRADIENT, 2, image.cols / 2);

    for (size_t i = 0; i < circles.size(); i++) {
        circle(src, Point(cvRound(circles[i][0]), cvRound(circles[i][1])), cvRound(circles[i][2]), Scalar(0, 0, 255), 2, LINE_AA);
    }

    imshow("Hough Circles", src);
    waitKey(0);
}

/**
 * Exercise 12-1
 * In this exercise, we learn to experiment with parameters by setting good
 * low Thresh and highThresh values in cv::Canny(). Load an image with suitably
 * interesting line structures. We’ll use three different high:low threshold
 * settings of 1.5:1, 2.75:1, and 4:1.
 *   a. Report what you see with a high setting of less than 50.
 *   b. Report what you see with a high setting between 50 and 100.
 *   c. Report what you see with a high setting between 100 and 150.
 *   d. Report what you see with a high setting between 150 and 200.
 *   e. Report what you see with a high setting between 200 and 250.
 *   f. Summarize your results and explain what happens as best you can.
 */
void exercise1() {
    Mat src = imread("../assets/img/ChongQing1.png");
    if (src.empty()) return;
    double high = 230;
    Mat dst1, dst2, dst3;
    // 1.5:1
    Canny(src, dst1, high / 1.5, high);
    imshow("1.5:1", dst1);
    // 2.75:1
    Canny(src, dst2, high / 2.75, high);
    imshow("2.75:1", dst2);
    // 4:1
    Canny(src, dst3, high / 4, high);
    imshow("4:1", dst3);
    waitKey(0);
}

int main(int argc, const char* argv[]) {
    exercise1();
    return 0;
}
