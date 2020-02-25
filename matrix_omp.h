//
// Created by а on 25.02.2020.
//

#ifndef NCGM_MATRIX_OMP_H
#define NCGM_MATRIX_OMP_H

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "matrix.h"


struct SquareMatrix zeroMatrixOPM(size_t size);
struct SquareMatrix eyeMatrixOMP(size_t size);
struct SquareMatrix randomMatrixOMP(size_t size);
struct SquareMatrix randomSymmetricMatrixOMP(size_t size);

struct SquareMatrix copyMatrixOMP(struct SquareMatrix m);
void copyToMatrixOMP(struct SquareMatrix from, struct SquareMatrix to);

struct Vector dotProductOMP(struct SquareMatrix m, struct Vector v);
struct Vector dotProductBufferedOMP(struct SquareMatrix m, struct Vector v, double *buffer);

#endif //NCGM_MATRIX_OMP_H
