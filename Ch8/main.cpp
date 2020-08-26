//
//  main.cpp
//  Ch8
//
//  Created by zz on 8/25/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <timer.h>

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
using namespace cv;
using namespace std;

/**
 * Example 8-1
 * Unpacking a four-character code to identify a video codec
 */
void ex1() {
    VideoCapture cap("../assets/video/Sampling.avi");
    unsigned f = (unsigned)cap.get(CAP_PROP_FOURCC);
    char fourcc[] = {
        (char)f,
        (char)(f >> 8),
        (char)(f >> 16),
        (char)(f >> 24),
        '\0'};
}

/**
 * Example 8-2
 * Using cv::FileStorage to create a .yml data file
 */
void ex2() {
    FileStorage fs("../output/test.yml", FileStorage::WRITE);

    fs << "frameCount" << 5;

    time_t rawtime;
    time(&rawtime);
    fs << "calibrationDate" << asctime(localtime(&rawtime));

    Mat cameraMatrix = (Mat_<double>(3, 3)
                            << 1000,
                        0, 320, 0, 1000, 240, 0, 0, 1);
    Mat distCoeffs = (Mat_<double>(5, 1)
                          << 0.1,
                      0.01, -0.001, 0, 0);
    fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;

    fs << "features"
       << "[";
    for (int i = 0; i < 3; i++) {
        int x = rand() % 640;
        int y = rand() % 480;
        uchar lbp = rand() % 256;

        fs << "{:"
           << "x" << x << "y" << y << "lbp"
           << "[:";
        for (int j = 0; j < 8; j++) {
            fs << ((lbp >> j) & 1);
        }
        fs << "]"
           << "}";
    }
    fs << "]";
    fs.release();
}

/**
 * Example 8-3
 * Using cv::FileStorage to read a .yml file
 */
void ex3() {
    FileStorage fs2("../output/test.yml", cv::FileStorage::READ);

    // first method: use (type) operator on FileNode.
    int frameCount = (int)fs2["frameCount"];

    // second method: use cv::FileNode::operator >> //
    string date;
    fs2["calibrationDate"] >> date;

    Mat cameraMatrix2, distCoeffs2;
    fs2["cameraMatrix"] >> cameraMatrix2;
    fs2["distCoeffs"] >> distCoeffs2;

    cout << "frameCount: " << frameCount << endl
         << "calibration date: " << date << endl
         << "camera matrix: " << cameraMatrix2 << endl
         << "distortion coeffs: " << distCoeffs2 << endl;

    FileNode features = fs2["features"];
    FileNodeIterator it = features.begin(), it_end = features.end();
    int idx = 0;
    vector<uchar> lbpval;
    // iterate through a sequence using FileNodeIterator
    for (; it != it_end; ++it, idx++) {
        cout << "feature #" << idx << ": ";

        cout << "x=" << (int)(*it)["x"] << ", y=" << (int)(*it)["y"] << ", lbp: (";

        // ( Note: easily read numerical arrays using FileNode >> std::vector. ) //
        (*it)["lbp"] >> lbpval;
        for (int i = 0; i < (int)lbpval.size(); i++) cout << " " << (int)lbpval[i];
        cout << ")" << endl;
    }
    fs2.release();
}

int main(int argc, const char* argv[]) {
    ex3();
    return 0;
}
