//
//  main.cpp
//  Ch6
//
//  Created by zz on 8/24/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

/**
 * Exercise 1
 * Drawing practice: load or create and display a color image.
 * Draw one example of every shape and line that OpenCV can draw.
 */
void exercise1() {
    Mat mat = imread("../assets/img/myAvatar.png");
    Point pts[4] = {Point(50, 30), Point(70, 25), Point(10, 160), Point(25, 60)};

    circle(mat, Point(90, 90), 50, Scalar(255, 0, 0));
    ellipse(mat, Point(90, 90), Size(50, 30), 45.f, 45.f, 360.f, Scalar(0, 0, 255));
    fillConvexPoly(mat, pts, 4, Scalar(0, 255, 0));
    rectangle(mat, Point(10, 10), Point(20, 20), Scalar(255, 0, 0));

    namedWindow("Exercise1", WINDOW_AUTOSIZE);
    imshow("Exercise1", mat);

    waitKey(0);
}

/**
 * Exercise 2
 * Grayscale: load and display a color image.
 *     a. Turn it into three-channel grayscale (it is still
 *        an BGR image, but it looks gray to the user).
 *     b. Draw color text onto the image.
 */
void exercise2() {
    Mat mat = imread("../assets/img/ChongQing1.png");
    Mat grayscale;
    cvtColor(mat, grayscale, COLOR_BGR2GRAY);
    putText(grayscale, "This is exercise 2", Point(100, 100), FONT_HERSHEY_COMPLEX, 1.f, Scalar(0, 255, 0));
    namedWindow("Exercise2", WINDOW_AUTOSIZE);
    imshow("Exercise2", grayscale);
    waitKey(0);
}

/**
 * Exercise 3
 * Dynamic text: load and display video from a video or from a camera.
 *     a. Draw a frame per second (FPS) counter somewhere on the image.
 */
void exercise3() {
    namedWindow("Exercise3", WINDOW_AUTOSIZE);
    VideoCapture capture;
    capture.open("../assets/video/Sampling.avi");
    Mat frame;
    int cnt = 1;
    for (;;) {
        capture >> frame;
        putText(frame, to_string(cnt++), Point(100, 100), FONT_HERSHEY_TRIPLEX, 1.0, Scalar(255, 255, 255));
        if (frame.empty()) break;
        imshow("Exercise3", frame);
        if (waitKey(1000) >= 0) break;
    }
}

/**
 * Exercise 4
 * Make a drawing program. Load or create an image and display it.
 *     a. Allow a user to draw a basic face.
 *     b. Make the components of the face editable (you will have
 *        to maintain a list of what was drawn, and when it is
 *        altered you might erase and redraw it the new size).
 */
void exercise4() {
    // pass
}

/**
 * Exercise 5
 * Use cv::LineIterator to count pixels on different line segments
 * in, say, a 300 × 300 image.
 *     a. At what angles do you get the same number of pixels for
 *        4-connected and 8-connected lines?
 *     b. For line segment angles other than the above, which counts
 *        more pixels: 4-connected or 8-connected lines?
 *     c. For a given line segment, explain the difference in the
 *        length of the line compared to the number of pixels you
 *        count iterating along the line for both 4-connected and
 *        8-connected? Which connectedness is closer to the true
 *        line length?
 */
void exercise5() {
    // a. Vertical and Horizontal
    // b. 4-conntected lines
    // c.
    Mat mat = imread("../assets/img/daxiong.png");
    LineIterator it4(mat, Point(0, 0), Point(300, 300), 4);
    LineIterator it8(mat, Point(0, 0), Point(300, 300), 8);
    cout << "4-connected: " << it4.count << " 8-connected: " << it8.count << endl;
}

int main(int argc, const char* argv[]) {
    exercise5();
    return 0;
}
