//
//  main.cpp
//  Ch5
//
//  Created by zz on 8/20/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

/**
 * Example 5-1. Complete program to alpha-blend the ROI starting at (0, 0)
 * in src2 with the ROI starting at (x, y) in src1
 */
void ex1(int x, int y, int w, int h, double alpha, double beta) {
    Mat src1 = imread("", 1);
    Mat src2 = imread("", 1);

    if (!src1.empty() && !src2.empty()) {
        Mat roi1(src1, Rect(x, y, w, h));
        Mat roi2(src2, Rect(0, 0, w, h));

        addWeighted(roi1, alpha, roi2, beta, 0.0, roi1);

        namedWindow("Alpha Blend", WINDOW_AUTOSIZE);
        imshow("Alpha Blend", src1);
        waitKey(0);
    }
}

/**
 * Exercise 1
 * This exercise will accustom you to the idea of many functions taking
 * matrix types. Create a two-dimensional matrix with three channels of
 * type byte with data size 100 × 100. Set all the values to 0.
 *     a. Draw a circle in the matrix using void cv::circle(InputOutputArray
 *     img, cv::point center, intradius, cv::Scalar color, int thickness=1,
 *     int line_type=8, int shift=0).
 *     b. Display this image using methods described in Chapter 2.
 */
void exercise1() {
    Mat mat(100, 100, CV_8UC3, Scalar(0));
    circle(mat, Point(50, 50), 40, Scalar(255, 255, 255));
    namedWindow("Exercise1", WINDOW_AUTOSIZE);
    imshow("Exercise1", mat);
    waitKey(0);
}

/**
 * Exercise 2
 * Create a two-dimensional matrix with three channels of type byte with
 * data size 100 × 100, and set all the values to 0. Use the cv::Mat
 * element access functions to modify the pixels. Draw a green rectangle
 * between (20, 5) and (40, 20).
 */
void exercise2() {
    Mat mat(100, 100, CV_8UC3, Scalar(0));
    for (int row = 20; row <= 40; row++) {
        for (int col = 5; col <= 20; col++) {
            mat.at<Vec3b>(row, col)[1] = 255;
        }
    }
    namedWindow("Exercise2", WINDOW_AUTOSIZE);
    imshow("Exercise2", mat);
    waitKey(0);
}

/**
 * Exercise 3
 * Create a three-channel RGB image of size 100 × 100. Clear it. Use
 * pointer arithmetic to draw a green square between (20, 5) and (40, 20).
 */
void exercise3() {
    Mat mat(100, 100, CV_8UC3);
    for (int row = 20; row <= 40; row++) {
        Vec3b* data = (Vec3b*)(mat.data + mat.step[0] * row);
        for (int col = 5; col <= 20; col++) {
            data[col][1] = 255;
        }
    }
    namedWindow("Exercise3", WINDOW_AUTOSIZE);
    imshow("Exercise3", mat);
    waitKey(0);
}

/**
 * Exercise 4
 * Practice using region of interest (ROI). Create a 210 × 210 single-
 * channel byte image and zero it. Within the image, build a pyramid
 * of increasing values using ROI and cv::Mat::setTo(). That is: the
 * outer border should be 0, the next inner border should be 20, the
 * next inner border should be 40, and so on until the final innermost
 * square is set to value 200; all borders should be 10 pixels wide.
 * Display the image.
 */
void exercise4() {
    Mat mat(210, 210, CV_8UC1, Scalar(0));
    Rect roi;
    int pos = 0, x = 0, y = 0;
    while (pos < 200) {
        roi = Rect(x, y, 210 - pos, 210 - pos);
        mat(roi).setTo(pos);
        pos += 20;
        x += 10;
        y += 10;
    }
    namedWindow("Exercise4", WINDOW_AUTOSIZE);
    imshow("Exercise4", mat);
    waitKey(0);
}

/**
 * Exercise 5
 * Use multiple headers for one image. Load an image that is at least 100 × 100.
 * Create two additional headers that are ROIs where width = 20 and the height
 * = 30. Their origins should be at (5, 10) and (50, 60), respectively. Pass
 * these new image subheaders to cv::bitwise_not(). Display the loaded image,
 * which should have two inverted rectangles within the larger image.
 */
void exercise5() {
    Mat mat = imread("../assets/img/myAvatar.png");
    Mat roi1(mat, Rect(5, 10, 20, 30)), roi2(mat, Rect(50, 60, 20, 30));
    bitwise_not(roi1, roi1);
    bitwise_not(roi2, roi2);
    namedWindow("Exercise5", WINDOW_AUTOSIZE);
    imshow("Exercise5", mat);
    waitKey(0);
}

/**
 * Exercise 6
 * Create a mask using cv::compare(). Load a real image. Use cv::split() to
 * split the image into red, green, and blue images.
 *     a. Find and display the green image.
 *     b. Clone this green plane image twice (call these clone1 and clone2).
 *     c. Find the green plane’s minimum and maximum value.
 *     d. Set clone1’s values to thresh = (unsigned char)((maximum - minimum)/ 2.0).
 *     e. Set clone2 to 0 and use cv::compare (green_image, clone1, clone2,
 *        cv::CMP_GE). Now clone2 will have a mask of where the value exceeds
 *        thresh in the green image.
 *     f. Finally, use cv::subtract  (green_image,thresh/2, green_image, clone2)
 *        and display the results.
 */
void exercise6() {
    Mat mat = imread("../assets/img/shotscreen.png");
    Mat rgb[3], green_image;
    for (int i = 0; i < 3; i++) {
        rgb[i] = Mat(mat.rows, mat.cols, mat.type());
    }
    split(mat, rgb);
    green_image = rgb[1];
    namedWindow("Exercise6", WINDOW_AUTOSIZE);
    imshow("Exercise6", green_image);
    Mat clone1 = green_image.clone(), clone2 = green_image.clone();
    double minVal, maxVal;
    minMaxLoc(green_image, &minVal, &maxVal);
    uchar threshold = (uchar)((maxVal - minVal) / 2.0);
    clone1.setTo(Scalar(threshold));
    clone2.setTo(Scalar(0));
    compare(green_image, clone1, clone2, CMP_GE);
    subtract(green_image, Scalar(threshold / 2), green_image, clone2);
    namedWindow("Exercise6_2", WINDOW_AUTOSIZE);
    imshow("Exercise6_2", green_image);
    waitKey(0);
}

int main(int argc, const char* argv[]) {
    exercise6();
    return 0;
}
