//
//  main.cpp
//  Ch2
//
//  Created by zz on 8/16/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// Example 2-1
void ex1() {
    cv::Mat img = cv::imread("../assets/img/zju.png", -1);
    if (img.empty()) return;
    cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example1", img);
    cv::waitKey(0);
    cv::destroyWindow("Example1");
}

// Example 2-2
void ex2() {
    Mat img = imread("../assets/img/zju.png", -1);
    if (img.empty()) return;
    namedWindow("Example1", WINDOW_AUTOSIZE);
    imshow("Example1", img);
    waitKey(0);
    destroyWindow("Example1");
}

// Example 2-3
void ex3() {
    namedWindow("Example3", WINDOW_AUTOSIZE);
    VideoCapture cap;
    cap.open("../assets/video/Sampling.avi");
    Mat frame;
    for (;;) {
        cap >> frame;
        if (frame.empty()) break;
        imshow("Example3", frame);
        if (waitKey(1000) >= 0) break;
    }
}

// Example 2-4
int g_slider_position = 0;
int g_run = 1, g_dontset = 0;  // start out in single step mode
VideoCapture g_cap;

void onTrackbarSlide(int pos, void*) {
    g_cap.set(CAP_PROP_POS_FRAMES, pos);
    if (!g_dontset) g_run = 1;
    g_dontset = 0;
}

void ex4() {
    namedWindow("Example2_4", WINDOW_AUTOSIZE);
    g_cap.open("../assets/video/Sampling.avi");
    int frames = (int)g_cap.get(CAP_PROP_FRAME_COUNT);
    int tmpw = (int)g_cap.get(CAP_PROP_FRAME_WIDTH);
    int tmph = (int)g_cap.get(CAP_PROP_FRAME_HEIGHT);
    cout << "Video has " << frames << " frames of dimensions(" << tmpw << ", " << tmph << ")." << endl;

    createTrackbar("Position", "Example2_4", &g_slider_position, frames, onTrackbarSlide);

    Mat frame;
    for (;;) {
        if (g_run != 0) {
            g_cap >> frame;
            if (frame.empty()) break;
            int current_pos = (int)g_cap.get(CAP_PROP_POS_FRAMES);
            g_dontset = 1;
            setTrackbarPos("Position", "Example2_4", current_pos);
            imshow("Example2_4", frame);
            g_run -= 1;
        }
        char c = (char)waitKey(10);
        if (c == 's') {
            // single step mode
            g_run = 1;
            cout << "Single step, run = " << g_run << endl;
        } else if (c == 'r') {
            // Run mode
            g_run = -1;
            cout << "Run mode, run = " << g_run << endl;
        } else if (c == 27) {
            break;
        }
    }
}

// Example 2-5
void ex5() {
    Mat image = imread("../assets/img/zju.png", -1);
    namedWindow("Example2_5-in", WINDOW_AUTOSIZE);
    namedWindow("Example2_5-out", WINDOW_AUTOSIZE);

    imshow("Example2_5-in", image);

    Mat out;

    GaussianBlur(image, out, Size(5, 5), 3, 3);
    GaussianBlur(out, out, Size(5, 5), 3, 3);

    imshow("Example2_5-out", out);

    waitKey(0);
}

// Example 2-6
void ex6() {
    Mat img1, img2;
    namedWindow("Example1", WINDOW_AUTOSIZE);
    namedWindow("Example2", WINDOW_AUTOSIZE);

    img1 = imread("../assets/img/zju.png", -1);
    imshow("Example1", img1);

    pyrDown(img1, img2);
    imshow("Example2", img2);

    waitKey(0);
}

// Example 2-7
void ex7() {
    Mat img_rgb, img_gry, img_cny;
    namedWindow("Example Gray", WINDOW_AUTOSIZE);
    namedWindow("Example Canny", WINDOW_AUTOSIZE);

    img_rgb = imread("../assets/img/ChongQing1.png");
    cvtColor(img_rgb, img_gry, COLOR_BGR2GRAY);
    imshow("Example Gray", img_gry);

    Canny(img_gry, img_cny, 10, 100, 3, true);
    imshow("Example Canny", img_cny);

    waitKey(0);
}

// Example 2-8
void ex8() {
    Mat img_rgb, img_gry, img_cny, img_pyr, img_pyr2;
    namedWindow("Example Gray", WINDOW_AUTOSIZE);
    namedWindow("Example Canny", WINDOW_AUTOSIZE);

    img_rgb = imread("../assets/img/ChongQing1.png");
    cvtColor(img_rgb, img_gry, COLOR_BGR2GRAY);
    pyrDown(img_gry, img_pyr);
    pyrDown(img_pyr, img_pyr2);
    imshow("Example Gray", img_pyr2);

    Canny(img_pyr2, img_cny, 10, 100, 3, true);
    imshow("Example Canny", img_cny);

    waitKey(0);
}

// Example 2-10
void ex10(int argc, const char* argv[]) {
    namedWindow("Example2_10", WINDOW_AUTOSIZE);

    VideoCapture cap;

    if (argc == 1) {
        cap.open(0);
    } else {
        cap.open(argv[1]);
    }
    if (!cap.isOpened()) {
        cerr << "Couldn't open capture." << endl;
    }
    Mat frame;
    for (;;) {
        cap >> frame;
        if (frame.empty()) break;
        imshow("Example2_10", frame);
        if (waitKey(1000) >= 0) break;
    }
}

// Example 2-11
void ex11() {
    namedWindow("Example2_11", WINDOW_AUTOSIZE);
    namedWindow("Log_Polar", WINDOW_AUTOSIZE);

    VideoCapture capture("../assets/video/Sampling.avi");

    double fps = capture.get(CAP_PROP_FPS);
    Size size((int)capture.get(CAP_PROP_FRAME_WIDTH), (int)capture.get(CAP_PROP_FRAME_HEIGHT));

    VideoWriter writer;
    writer.open("../assets/video/logPolar.avi", writer.fourcc('M', 'J', 'P', 'G'), fps, size);

    Mat logpolar_frame, bgr_frame;
    for (;;) {
        capture >> bgr_frame;
        if (bgr_frame.empty()) break;

        imshow("Example2_11", bgr_frame);

        logPolar(bgr_frame, logpolar_frame, Point2f(bgr_frame.cols / 2, bgr_frame.rows / 2), 40, WARP_FILL_OUTLIERS);

        imshow("Log_Polar", logpolar_frame);

        writer << logpolar_frame;

        char c = waitKey(0);
        if (c == 27) break;
    }
    capture.release();
}

// Exercise 3 & 4
void exercise3And4() {
    namedWindow("Exercise3", WINDOW_AUTOSIZE);
    namedWindow("DownSampled", WINDOW_AUTOSIZE);

    VideoCapture capture("../assets/video/Sampling.avi");

    double fps = capture.get(CAP_PROP_FPS);
    Size size((int)(capture.get(CAP_PROP_FRAME_WIDTH) + 1) / 2, (int)(capture.get(CAP_PROP_FRAME_HEIGHT) + 1) / 2);

    VideoWriter writer;
    writer.open("../assets/video/downsampled.avi", writer.fourcc('M', 'J', 'P', 'G'), fps, size);

    Mat downsampled_frame, bgr_frame;
    for (;;) {
        capture >> bgr_frame;
        if (bgr_frame.empty()) break;

        imshow("Exercise3", bgr_frame);

        pyrDown(bgr_frame, downsampled_frame);

        imshow("DownSampled", downsampled_frame);

        writer << downsampled_frame;

        char c = waitKey(0);
        if (c == 27) break;
    }
    capture.release();
}

// Exercise 5
int g_position = 0, g_step = 1;
VideoCapture g_capture;

void onTrackbarSlideCallback(int pos, void*) {
    g_capture.set(CAP_PROP_POS_FRAMES, pos);
    g_step = 1;
}

void exercise5() {
    namedWindow("Exercise5", WINDOW_AUTOSIZE);
    g_capture.open("../assets/video/Sampling.avi");
    int frames = (int)g_capture.get(CAP_PROP_FRAME_COUNT);

    createTrackbar("Position", "Exercise5", &g_position, frames, onTrackbarSlideCallback);

    Mat frame, downsampled_frame;
    for (;;) {
        if (g_step == 1) {
            g_capture >> frame;
            if (frame.empty()) break;
            pyrDown(frame, downsampled_frame);
            int current_pos = (int)g_capture.get(CAP_PROP_POS_FRAMES);
            setTrackbarPos("Position", "Exercise5", current_pos - 1);
            imshow("Exercise5", downsampled_frame);
            g_step--;
        }
        char c = (char)waitKey(10);
        if (c == 27) {
            break;
        }
    }
}

int main(int argc, const char* argv[]) {
    exercise5();
    return 0;
}
