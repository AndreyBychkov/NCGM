//
// Created by а on 14.12.2019.
//

#ifndef TEST_MATRIX_H
#define TEST_MATRIX_H

#include "vector.h"

struct SquareMatrix {
    int size;
    double **matrix;
};

struct SquareMatrix initMatrix(int size);
struct SquareMatrix zeroMatrix(int size);
struct SquareMatrix eyeMatrix(int size);
void freeMatrix(struct SquareMatrix m);

void printMatrix(struct SquareMatrix m);

struct SquareMatrix readMatrixFromStdIn();
struct SquareMatrix readMatrixFromStdInSized(int size);

struct SquareMatrix copyMatrix(struct SquareMatrix m);
void copyToMatrix(struct SquareMatrix from, struct SquareMatrix to);

struct Vector getColumn(struct SquareMatrix m,int index);
struct Vector getRow(struct SquareMatrix m, int index);

struct Vector dotProduct(struct SquareMatrix m, struct Vector v);
struct Vector dotProductParallel(struct SquareMatrix m, struct Vector v);

struct SquareMatrix randomMatrix(int size);

#endif //TEST_MATRIX_H
