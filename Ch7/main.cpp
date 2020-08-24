//
//  main.cpp
//  Ch7
//
//  Created by zz on 8/24/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
using namespace std;

/**
 * Example 7-1
 * Using the default random number generator to generate a pair of
 * integers and a pair of floating-point numbers
 */
void ex1() {
    RNG rng = theRNG();
    cout << "An integer:      " << (int)rng << endl;
    cout << "Another Integer: " << int(rng) << endl;
    cout << "A float:         " << (float)rng << endl;
    cout << "Another float:   " << float(rng) << endl;
}

/**
 * Exercise 1
 * Using the cv::RNG random number generator:
 *     a. Generate and print three floating-point numbers, each
 *        drawn from a uniform distribution from 0.0 to 1.0.
 *     b. Generate and print three double-precision numbers, each
 *        drawn from a Gaussian distribution centered at 0.0 and
 *        with a standard deviation of 1.0.
 *     c. Generate and print three unsigned bytes, each drawn from
 *        a uniform distribution from 0 to 255.
 */
void exercise1() {
    RNG rng;

    // a.
    for (int i = 0; i < 3; i++) cout << rng.uniform(0.f, 1.f) << " ";
    cout << endl;

    // b.
    for (int i = 0; i < 3; i++) cout << rng.gaussian(1.0) << " ";
    cout << endl;

    // c.
    for (int i = 0; i < 3; i++) cout << rng(255) << " ";
}

/**
 * Exercise 2
 * Using the fill() method of the cv::RNG random number generator, create an array of:
 *     a. 20 floating-point numbers with a uniform distribution from 0.0 to 1.0.
 *     b. 20 floating-point numbers with a Gaussian distribution centered at 0.0 and with a standard deviation of 1.0.
 *     c. 20 unsigned bytes with a uniform distribution from 0 to 255.
 *     d. 20 color triplets, each of three bytes with a uniform distribution from 0 to 255.
 */
void exercise2() {
    RNG rng;
    Mat mat(20, 1, CV_32FC1), mat1(20, 1, CV_8UC1), mat2(20, 1, CV_8UC3);
    // a
    rng.fill(mat, RNG::UNIFORM, 0.f, 1.f);
    for (int i = 0; i < mat.rows; i++) {
        cout << mat.at<float>(i) << " ";
    }
    cout << endl;

    // b
    rng.fill(mat, RNG::NORMAL, 0.f, 1.f);
    for (int i = 0; i < mat.rows; i++) {
        cout << mat.at<float>(i) << " ";
    }
    cout << endl;

    // c
    rng.fill(mat1, RNG::UNIFORM, 0, 255);
    for (int i = 0; i < mat1.rows; i++) {
        cout << mat1.at<uchar>(i) << " ";
    }
    cout << endl;

    // d
    rng.fill(mat2, RNG::UNIFORM, 0, 255);
    for (int i = 0; i < mat2.rows; i++) {
        for (int j = 0; j < 3; j++) {
            cout << mat2.at<Vec3i>(i)[j] << " ";
        }
        cout << endl;
    }
}

/**
 * Exercise 3
 * Using the cv::RNG random number generator, create an array of 100 three-
 * byte objects such that:
 *     a. The first and second dimensions have a Gaussian distribution,
 *        centered at 64 and 192, respectively, each with a variance of 10.
 *     b. The third dimension has a Gaussian distribution, centered at 128
 *        and with a variance of 2.
 *     c. Using the cv::PCA object, compute a projection for which maxComponents=2.
 *     d. Compute the mean in both dimensions of the projection; explain the result.
 */
void exercise3() {
    RNG rng;
    Mat mat(100, 1, CV_8UC3), output1, output2;
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            for (int k = 0; k < 3; k++) {
                if (k == 1)
                    mat.at<Vec3i>(i, j)[k] = rng.gaussian(10) + 64;
                else if (k == 2)
                    mat.at<Vec3i>(i, j)[k] = rng.gaussian(10) + 192;
                else
                    mat.at<Vec3i>(i, j)[k] = rng.gaussian(2) + 128;
            }
        }
    }
    PCA pca(mat, noArray(), PCA::DATA_AS_ROW, 2);
    output1 = pca.project(mat);
    cout << "ROW: " << mean(output1) << endl;
    pca(mat, noArray(), PCA::DATA_AS_COL, 2);
    output2 = pca.project(mat);
    cout << "COL: " << mean(output2) << endl;

    // pass
}

int main(int argc, const char* argv[]) {
    exercise3();
    return 0;
}
