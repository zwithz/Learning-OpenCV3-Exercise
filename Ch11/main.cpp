//
//  main.cpp
//  Ch11
//
//  Created by zz on 8/29/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

/**
 * Example 11-1
 * An affine transformation
 */
void ex1() {
    Mat src = imread("../assets/img/ChongQing1.png");
    if (src.empty()) return;

    Point2f srcTri[] = {
        Point2f(0, 0),             // src Top left
        Point2f(src.cols - 1, 0),  // src Top right
        Point2f(0, src.rows - 1)   // src Bottom left
    };

    Point2f dstTri[] = {
        Point2f(src.cols * 0.f, src.rows * 0.33f),    //dst Top left
        Point2f(src.cols * 0.85f, src.rows * 0.25f),  // dst Top right
        Point2f(src.cols * 0.15f, src.rows * 0.7f)    // dst Bottom left
    };

    // Compute affine matrix
    Mat wrap_mat = getAffineTransform(srcTri, dstTri);
    Mat dst, dst2;
    warpAffine(src, dst, wrap_mat, src.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar());
    for (int i = 0; i < 3; i++)
        circle(dst, dstTri[i], 5, Scalar(255, 0, 255), -1, LINE_AA);

    imshow("Affine Transform Test", dst);
    waitKey(0);

    for (int frame = 0;; frame++) {
        // Compute ratation matrix
        Point2f center(src.cols * 0.5f, src.rows * 0.5f);
        double angle = frame * 3 % 360, scale = (cos((angle - 60) * CV_PI / 180) + 1.05) * 0.8;

        Mat rot_mat = getRotationMatrix2D(center, angle, scale);

        warpAffine(src, dst, rot_mat, src.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar());

        imshow("Rotated Image", dst);
        if (waitKey(30) >= 0) break;
    }
}

/**
 * Example 11-2
 * Code for perspective transformation
 */
void ex2() {
    Mat src = imread("../assets/img/ChongQing1.png");
    if (src.empty()) return;

    Point2f srcQuad[] = {
        Point2f(0, 0),                        // src Top left
        Point2f(src.cols - 1, 0),             //src Top right
        Point2f(src.cols - 1, src.rows - 1),  // src Bottom right
        Point2f(0, src.rows - 1)              // src Bottom left
    };

    Point2f dstQuad[] = {
        Point2f(src.cols * 0.05f, src.rows * 0.33f),
        Point2f(src.cols * 0.9f, src.rows * 0.25f),
        Point2f(src.cols * 0.8f, src.rows * 0.9f),
        Point2f(src.cols * 0.2f, src.rows * 0.7f)};

    // Compute perspective matrix
    Mat warp_mat = getPerspectiveTransform(srcQuad, dstQuad);
    Mat dst;
    warpPerspective(src, dst, warp_mat, src.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar());
    for (int i = 0; i < 4; i++) {
        circle(dst, dstQuad[i], 5, Scalar(255, 0, 255), -1, LINE_AA);
    }
    imshow("Perspective Transform Test", dst);
    waitKey(0);
}

/**
 * Example 11-3
 * Log-polar transform example
 */
void ex3() {
    Mat src = imread("../assets/img/ChongQing1.png", 1);
    if (src.empty()) return;

    double M = 10;

    Mat dst(src.size(), src.type()), src2(src.size(), src.type());

    logPolar(src, dst, Point2f(src.cols * 0.5f, src.rows * 0.5f), M, INTER_LINEAR | WARP_FILL_OUTLIERS);

    logPolar(dst, src2, Point2f(src.cols * 0.5f, src.rows * 0.5f), M, INTER_LINEAR | WARP_INVERSE_MAP);

    imshow("log-polar", dst);
    imshow("inverse log-polar", src2);

    waitKey(0);
}

/**
 * Exercise 11-1
 * Find and load a picture of a face where the face is frontal,
 * has eyes open, and takes up most or all of the image area.
 * Write code to find the pupils of the eyes.
 */
void exercise1() {
    Mat src = imread("../assets/img/front_face.jpg");
    if (src.empty()) return;

    Mat gray, tmp, dst;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    // Laplacian pyramids
    pyrDown(gray, tmp);
    pyrUp(tmp, tmp);
    tmp = gray - tmp;
    threshold(tmp, dst, 85.f, 255.f, THRESH_BINARY);
    imshow("Exercise 11-1 two pupils", dst);
    double minPixelValue, maxPixelValue;
    Point minPixelPoint, maxPixelPoint;
    minMaxLoc(tmp, &minPixelValue, &maxPixelValue, &minPixelPoint, &maxPixelPoint);
    circle(src, maxPixelPoint, 10, Scalar(255, 255, 255), 2);
    imshow("Exercise 11-1", src);
    waitKey(0);
}

/**
 * Exercise 11-2
 * Look at the diagrams of how the log-polar function transforms
 * a square into a wavy line.
 *   a. Draw the log-polar results if the log-polar center point
 *      were sitting on one of the corners of the square.
 *   b. What would a circle look like in a log-polar transform
 *      if the center point were inside the circle and close to
 *      the edge?
 *   c. Draw what the transform would look like if the center
 *      point were sitting just outside of the circle.
 */
void exercise2() {
    // a
    Mat srcA(512, 512, CV_8UC1);
    Point leftTop(100, 100), rightBottom(412, 412);
    rectangle(srcA, leftTop, rightBottom, Scalar(255, 255, 255));
    Mat dstA(srcA.size(), srcA.type());
    imshow("Exercise 11-2 srcA", srcA);
    logPolar(srcA, dstA, Point2f(412.f, 412.f), 50.00, INTER_LINEAR);
    imshow("Exercise 11-2 a", dstA);

    // b
    Mat srcB(512, 512, CV_8UC1);
    circle(srcB, Point(256, 256), 100, Scalar(255, 255, 255));
    imshow("Exercise 11-2 srcB", srcB);
    Mat dstB(srcB.size(), srcB.type());
    logPolar(srcB, dstB, Point2f(170.f, 170.f), 50.00, INTER_LINEAR);
    imshow("Exercise 11-2 b", dstB);

    // c
    Mat dstC(srcB.size(), srcB.type());
    logPolar(srcB, dstC, Point2f(100.f, 100.f), 50.00, INTER_LINEAR);
    imshow("Exercise 11-2 c", dstC);
    waitKey(0);
}

int main(int argc, const char* argv[]) {
    exercise2();
    return 0;
}
