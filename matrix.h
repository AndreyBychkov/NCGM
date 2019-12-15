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
void freeMatrix(struct SquareMatrix m);

void printMatrix(struct SquareMatrix m);

struct SquareMatrix readMatrixFromStdIn();

struct Vector getColumn(struct SquareMatrix m,int index);
struct Vector getRow(struct SquareMatrix m, int index);

struct Vector dotProduct(struct SquareMatrix m, struct Vector v);

#endif //TEST_MATRIX_H
