//
//  main.cpp
//  Ch3
//
//  Created by zz on 8/18/20.
//  Copyright © 2020 zwithz. All rights reserved.
//

#include <iostream>
#include <opencv2/core.hpp>
using namespace cv;
using namespace std;

/**
 * Exercise 1
 * b. cv_IABS() cvRound() cvCeil() cvFloor()
 * c. cvRandInt() cvRandReal()
 * d. cvPointTo32f() cvPointFrom32f()
 */

// Exercise 2
void exercise2() {
    Matx33f mat33f(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Vec3f vec3f(1, 2, 3);
    Vec3f res = mat33f * vec3f;
    cout << res;
}

// Exercise 3
void exercise3() {
    Matx<float, 3, 3> mat33f(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Vec<float, 3> vec3f(1, 2, 3);
    Vec3f res = mat33f * vec3f;
    cout << res << endl;
    Matx<float, 3, 1> mat31f(vec3f);
    cout << mat31f;
}

int main(int argc, const char* argv[]) {
    exercise3();
    return 0;
}
