//
//  main.cpp
//  Ch4
//
//  Created by zz on 8/19/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
using namespace std;

/**
 * Example 4-1. Summation of a multidimensional array, done plane by plane
 */
void ex1() {
    const int n_mat_size = 5;
    const int n_mat_sz[] = {n_mat_size, n_mat_size, n_mat_size};
    Mat n_mat(3, n_mat_sz, CV_32FC1);

    RNG rng;
    rng.fill(n_mat, RNG::UNIFORM, 0.f, 1.f);

    const Mat* arrays[] = {&n_mat, 0};
    Mat my_planes[1];
    NAryMatIterator it(arrays, my_planes);

    // On each iteration, it.planes[i] will be the current plane of the
    // i-th array from 'arrays'.
    float s = 0.f;  // Total sum over all planes
    int n = 0;      // Total number of planes
    for (int p = 0; p < it.nplanes; p++, it++) {
        s += sum(it.planes[0])[0];
        n++;
    }
    cout << s << " " << n << endl;
}

/**
 * Example 4-2. Summation of two arrays using the N-ary operator
 */
void ex2() {
    const int n_mat_size = 5;
    const int n_mat_sz[] = {n_mat_size, n_mat_size, n_mat_size};
    Mat n_mat0(3, n_mat_sz, CV_32FC1);
    Mat n_mat1(3, n_mat_sz, CV_32FC1);

    RNG rng;
    rng.fill(n_mat0, RNG::UNIFORM, 0.f, 1.f);
    rng.fill(n_mat1, RNG::UNIFORM, 0.f, 1.f);

    const Mat* array[] = {&n_mat0, &n_mat1, 0};
    Mat my_planes[2];
    NAryMatIterator it(array, my_planes);

    float s = 0.f;  // Total sum over all planes in both arrays
    int n = 0;      // Total number of planes
    for (int p = 0; p < it.nplanes; p++, it++) {
        s += sum(it.planes[0])[0];
        s += sum(it.planes[1])[0];
        n++;
    }
    cout << s << " " << n << endl;
}

/**
 * Example 4-3. Printing all of the nonzero elements of a sparse array
 */
void ex3() {
    // Create a 10x10 sparse matrix with a few nonzero elements
    int size[] = {10, 10};
    SparseMat sm(2, size, CV_32F);

    for (int i = 0; i < 10; i++) {
        int idx[2];
        idx[0] = size[0] * rand();
        idx[1] = size[1] * rand();
        sm.ref<float>(idx) += 1.0f;
    }

    // Print out the nonzero elements
    SparseMatConstIterator_<float> it = sm.begin<float>();
    SparseMatConstIterator_<float> it_end = sm.end<float>();

    for (; it != it_end; it++) {
        const SparseMat::Node* node = it.node();
        printf("(%3d, %3d) %f\n", node->idx[0], node->idx[1], *it);
    }
}

/**
 * Example 4-4. A better way to print a matrix
 */
template <typename T>
void print_matrix(const SparseMat_<T>* sm) {
    SparseMatConstIterator_<T> it = sm->begin();
    SparseMatConstIterator_<T> it_end = sm->end();

    for (; it != it_end; it++) {
        const typename SparseMat_<T>::Node* node = it.node();
        cout << "(" << node->idx[0] << ", " << node->idx[1] << ") = " << *it << endl;
    }
}

/**
 * Exercise 1. Create a 500 × 500 single channel uchar image with every pixel
 * equal to zero.
 *     a. Create an ASCII numeric typewriter where you can type numbers into
 *     your computer and have the number show up in a 20-pixel-high by 10-
 *     pixel-wide block. As you type, the numbers will display from left to
 *     right until you hit the end of the image. Then just stop.
 *     b. Allow for carriage return and backspace.
 *     c. Allow for arrow keys to edit each number.
 *     d. Create a key that will convert the resulting image into a color
 *     image, each number taking on a different color.
 */

/**
 * Exercise 2. We want to create a function that makes it efficient to sum up rectangular regions in an image by creating a statistics image where each “pixel” holds the sum of the rectangle from that point to the image origin. These are called integral images and by using just 4 points from the integral image, you can determine the sum of any rectangle in the image.
 *     a. Create a 100 × 200 single-channel uchar image with random numbers. Create a 100 × 200 single-channel float “integral image” with all members equal to zero.
 *     b. Fill in each element of the integral image with the corresponding sum of the rectangle from that pixel to the origin in the original uchar image.
 *     c. How can you do part b) very efficiently in one pass using the integral numbers you’ve already calculated in the integral image plus the new number being added in the original image? Implement this efficient method.
 *     d. Use the integral image to rapidly calculate the sum of pixels in any rectangle in the original image.
 *     e. How can you modify the integral image so that you can compute the sum of a 45-degree rotated rectangle in the original image very efficiently? Describe the algorithm.
 */
void exercise2() {
    const int display_width = 100;
    const int display_height = 200;
    Mat1b original_image(display_height, display_width);
    Mat1f integral_image(display_height, display_width);
    RNG rng(0);
    rng.fill(original_image, RNG::UNIFORM, 0, 255);
    integral_image = 0;

    namedWindow("Original Image", WINDOW_AUTOSIZE);
    imshow("Original Image", original_image);

    for (int i = 0; i < display_height; i++) {
        integral_image.at<float>(i, 0) = sum(original_image.rowRange(0, i + 1).colRange(0, 1))[0];
    }
    for (int i = 0; i < display_width; i++) {
        integral_image.at<float>(0, i) = sum(original_image.rowRange(0, 1).colRange(0, i + 1))[0];
    }

    for (int i = 1; i < display_height; i++) {
        for (int j = 1; j < display_width; j++) {
            integral_image.at<float>(i, j) = (float)original_image.at<uchar>(i, j) + integral_image.at<float>(i - 1, j) + integral_image.at<float>(i, j - 1) - integral_image.at<float>(i - 1, j - 1);
        }
    }

    integral_image /= integral_image.at<float>(display_height - 1, display_width - 1);

    cv::namedWindow("Integral Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Integral Image", integral_image);

    cv::waitKey(0);

}

int main(int argc, const char* argv[]) {
    exercise2();
    return 0;
}
