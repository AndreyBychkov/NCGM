//
// Created by а on 14.12.2019.
//

#ifndef TEST_MATRIX_H
#define TEST_MATRIX_H

struct SquareMatrix {
    int size;
    double **matrix;
};

struct SquareMatrix initMatrix(int size);
void freeMatrix(struct SquareMatrix m);

void printMatrix(struct SquareMatrix m);

struct SquareMatrix readMatrixFromStdIn();

#endif //TEST_MATRIX_H
