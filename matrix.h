//
// Created by а on 14.12.2019.
//

#ifndef TEST_MATRIX_H
#define TEST_MATRIX_H

#include "stdlib.h"
#include "vector.h"

struct SquareMatrix {
    size_t size;
    double *matrix;
};

struct SquareMatrix initMatrix(size_t size);
struct SquareMatrix zeroMatrix(size_t size);
struct SquareMatrix eyeMatrix(size_t size);
struct SquareMatrix randomMatrix(size_t size);
void freeMatrix(struct SquareMatrix m);

void printMatrix(struct SquareMatrix m);

struct SquareMatrix readMatrixFromStdIn();
struct SquareMatrix readMatrixFromStdInSized(size_t size);

struct SquareMatrix copyMatrix(struct SquareMatrix m);
void copyToMatrix(struct SquareMatrix from, struct SquareMatrix to);

struct Vector getColumn(struct SquareMatrix m, size_t index);
struct Vector getRow(struct SquareMatrix m, size_t index);
void getColumnBuffered(struct SquareMatrix m, size_t index, double *buffer);
void getRowBuffered(struct SquareMatrix m, size_t index, double *buffer);

struct Vector dotProduct(struct SquareMatrix m, struct Vector v);
void dotProductBuffered(struct SquareMatrix m, struct Vector v, double *buffer);

#endif //TEST_MATRIX_H
