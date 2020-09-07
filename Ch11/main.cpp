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

int main(int argc, const char* argv[]) {
    ex2();
    return 0;
}
