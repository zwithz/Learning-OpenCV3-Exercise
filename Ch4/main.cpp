//
//  main.cpp
//  Ch4
//
//  Created by zz on 8/19/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv2/core.hpp>
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

int main(int argc, const char* argv[]) {
    ex2();
    return 0;
}
