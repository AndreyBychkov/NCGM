//
// Created by а on 15.12.2019.
//

#include "../matrix.h"
#include <math.h>
#include "matrix_tests.h"

void testMatrixCreation() {
    struct SquareMatrix m = initMatrix(5);

    if (m.matrix == NULL) {
        printf("testMatrixCreation: FAILED. Memory is not allocated. \n");
    } else if (m.size != 5) {
        printf("testMatrixCreation: FAILED. Size is incorrect. \n");
    } else {
        printf("testMatrixCreation: PASSED. \n");
    }
}

void testZero() {
    struct SquareMatrix m = zeroMatrix(3);
    for (size_t i = 0; i < m.size; ++i) {
        for (size_t j = 0; j < m.size; ++j) {
            if (fabs(m.matrix[m.size * i + j]) > 10e-6) {
                printf("testZero: FAILED. Contains element non-zero element: %lf. \n", m.matrix[m.size * i + j]);
                return;
            }
        }
    }
    printf("testZero: PASSED. \n");
}

void testEye() {
    struct SquareMatrix m = eyeMatrix(3);
    for (size_t i = 0; i < m.size; ++i) {
        for (size_t j = 0; j < m.size; ++j) {
            if (i != j && fabs(m.matrix[m.size * i + j]) > 10e-6) {
                printf("testEye: FAILED. Contains element non-zero element: %lf outside of diagonal. \n", m.matrix[m.size * i + j]);
                return;
            }
            if (i == j && fabs(m.matrix[m.size * i + j] - 1.0) > 10e-6) {
                printf("testEye: FAILED. Contains element in diagonal: %lf != 1. \n", m.matrix[m.size * i + j]);
                return;
            }
        }
    }
    printf("testEye: PASSED. \n");
}

void testGetColumn() {
    struct SquareMatrix m = initMatrix(3);

    size_t counter = 0;
    for (size_t i = 0; i < m.size; ++i) {
        for (size_t j = 0; j < m.size; ++j) {
            m.matrix[m.size * i + j] = counter;
            ++counter;
        }
    }

    struct Vector expected = initVector(m.size);
    expected.vector[0] = 2;
    expected.vector[1] = 5;
    expected.vector[2] = 8;

    struct Vector result = getColumn(m, 1);

    double epsilon = 10e-6;
    for (size_t i = 0; i < expected.size; ++i) {
        if (fabs(expected.vector[i] - result.vector[i]) < epsilon) {
            printf("testGetColumn: FAILED. At index %d result %lf != expected %lf \n",
                   i, result.vector[i], expected.vector[i]);
            return;
        }
    }
    printf("testGetColumn: PASSED. \n");
}

void testGetRow() {
    struct SquareMatrix m = initMatrix(3);

    size_t counter = 0;
    for (size_t i = 0; i < m.size; ++i) {
        for (size_t j = 0; j < m.size; ++j) {
            m.matrix[m.size * i + j] = counter;
            ++counter;
        }
    }

    struct Vector expected = initVector(m.size);
    expected.vector[0] = 4;
    expected.vector[1] = 5;
    expected.vector[2] = 6;

    struct Vector result = getRow(m, 1);

    double epsilon = 10e-6;
    for (size_t i = 0; i < expected.size; ++i) {
        if (fabs(expected.vector[i] - result.vector[i]) < epsilon) {
            printf("testGetRow: FAILED. At index %d result %lf != expected %lf \n",
                   i, result.vector[i], expected.vector[i]);
            return;
        }
    }
    printf("testGetRow: PASSED. \n");
}

void testDotProduct() {
    struct Vector v = initVector(3);
    v.vector[0] = 1;
    v.vector[1] = 2;
    v.vector[2] = 3;

    struct SquareMatrix m = initMatrix(3);
    for (size_t i = 0; i < m.size; ++i) {
        for (size_t j = 0; j < m.size; ++j) {
            m.matrix[m.size * i + j] = (double)(i + j);
        }
    }

    struct Vector result = dotProduct(m, v);
    struct Vector expected = initVector(3);
    expected.vector[0] = 8;
    expected.vector[1] = 14;
    expected.vector[2] = 20;

    for (size_t i = 0; i < result.size; ++i) {
        if (fabs(expected.vector[i] - result.vector[i]) > 1e-6) {
            printf("testDotProduct: FAILED. At index %d result %lf != expected %lf \n",
                    i, result.vector[i], expected.vector[i]);
            return;
        }
    }
    printf("testDotProduct: PASSED \n");
}

void matrixTestSuite() {
    for (size_t i = 0; i < 40; ++i) putchar('-');
    printf("\nMatrix tests:\n\n");
    testMatrixCreation();
    testZero();
    testEye();
    testGetRow();
    testGetColumn();
    testDotProduct();

}


