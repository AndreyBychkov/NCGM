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
    } else if (v.size != 5) {
        printf("testVectorCreation: FAILED. Size is incorrect. \n");
    } else {
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
    } else {
        printf("testScalarComposition: FAILED. Incorrect result: 20 != %lf. \n", result);
    }
}


void testAddVector() {
    struct Vector first = zeroVector(3);
    struct Vector second = onesVector(3);

    struct Vector result = addVector(first, second);
    struct Vector expected = onesVector(3);

    if (equalsVector(result, expected)) {
        printf("testAddVector: PASSED. \n");
    } else {
        printf("testAddVector: FAILED. \n");
    }
}

void testSubtractVector() {
    struct Vector first = zeroVector(3);
    struct Vector second = onesVector(3);

    struct Vector result = subtractVector(first, second);
    struct Vector expected = onesVector(3);
    minusMutable(expected);

    if (equalsVector(result, expected)) {
        printf("testSubtractVector: PASSED. \n");
    } else {
        printf("testSubtractVector: FAILED. \n");
    }
}

void testMAE() {
    struct Vector first = zeroVector(3);
    struct Vector second = initVector(3);
    second.vector[0] = 1;
    second.vector[1] = 2;
    second.vector[2] = 3;

    if (fabs(meanAbsoluteErrorVector(first, second) - 6.0) < 1e-6) {
        printf("testMAE: PASSED. \n");
    } else {
        printf("testMAE: FAILED. \n");
    }
}

void vectorTestSuite() {
    for (int i = 0; i < 40; ++i) putchar('-');
    printf("\nVector tests:\n\n");
    testVectorCreation();
    testScalarComposition();
    testAddVector();
    testSubtractVector();
    testMAE();
}






