//
// Created by а on 15.12.2019.
//

#include "vector_tests.h"
#include "../vector.h"
#include <math.h>

void testVectorCreation() {
    struct Vector v = initVector(5);

    if (v.vector == NULL) {
        printf("testVectorCreation: FAILED. Memory is not allocated. \n");
    }
    else if (v.size != 5) {
        printf("testVectorCreation: FAILED. Size is incorrect. \n");
    }
    else {
        printf("testVectorCreation: PASSED. \n");
    }

    freeVector(v);
}

void testScalarComposition() {
    int size = 3;
    struct Vector v1 = initVector(size);
    struct Vector v2 = initVector(size);

    for (int i = 0; i < size; ++i) {
        v1.vector[i] = i + 1; // Will generate 1 2 3
        v2.vector[i] = i + 2; // Will generate 2 3 4
    }

    double result = scalarComposition(v1, v2);
    double epsilon = 1e-6;
    if (fabs(result - 20.0) < epsilon) {
        printf("testScalarComposition: PASSED. \n");
    }
    else {
        printf("testScalarComposition: FAILED. Incorrect result: 20 != %lf. \n", result);
    }
}

void vectorTestSuite() {
    testVectorCreation();
    testScalarComposition();
}

