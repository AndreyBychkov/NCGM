//
// Created by а on 25.02.2020.
//

#include "matrix_omp.h"


struct SquareMatrix zeroMatrixOPM(size_t size) {
    struct SquareMatrix m = initMatrix(size);
    #pragma omp parallel default(none) shared(m, size)
    {
        #pragma omp for
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                m.matrix[m.size * i + j] = 0.0;
            }
        }
    }
    return m;
}
struct SquareMatrix eyeMatrixOMP(size_t size) {
    struct SquareMatrix m = zeroMatrix(size);
    #pragma omp parallel default(none) shared(m, size)
    {
        #pragma omp for
        for (size_t i = 0; i < size; ++i) {
            m.matrix[m.size * i + i] = 1.0;
        }
    }
    return m;
}
struct SquareMatrix randomMatrixOMP(size_t size) {
    struct SquareMatrix m = initMatrix(size);
    #pragma omp parallel default(none) shared(m, size)
    {
        #pragma omp for
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                m.matrix[m.size * i + j] = rand() % 10;
            }
        }
    }
    return m;
}
struct SquareMatrix randomSymmetricMatrixOMP(size_t size) {
    struct SquareMatrix m = initMatrix(size);
    #pragma omp parallel default(none) shared(m, size)
    {
        #pragma omp for
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = i; j < size; ++j) {
                double randVal = rand() % 10;
                m.matrix[m.size * i + j] = randVal;
                m.matrix[m.size * j + i] = randVal;
            }
        }
    }
    return m;
}

struct SquareMatrix copyMatrixOMP(struct SquareMatrix m) {
    struct SquareMatrix result = initMatrix(m.size);
    #pragma omp parallel default(none) shared(m, result)
    {
        #pragma omp for
        for (size_t i = 0; i < m.size; ++i) {
            for (size_t j = 0; j < m.size; ++j) {
                result.matrix[m.size * i + j] = m.matrix[m.size * i + j];
            }
        }
    }
    return result;
}
void copyToMatrixOMP(struct SquareMatrix from, struct SquareMatrix to) {
    #pragma omp parallel default(none) shared(from, to)
    {
        #pragma omp for
        for (size_t i = 0; i < from.size; ++i) {
            for (size_t j = 0; j < from.size; ++j) {
                to.matrix[to.size * i + j] = from.matrix[from.size * i + j];
            }
        }
    }
}

struct Vector dotProductOMP(struct SquareMatrix m, struct Vector v) {
    const size_t size = v.size;
    struct Vector result = initVector(size);
    #pragma omp parallel default(none) shared(m, v, result)
    {
        #pragma omp for
        for (size_t i = 0; i < size; ++i) {
            struct Vector row = getRow(m, i);
            result.vector[i] = scalarComposition(row, v);
            freeVector(row);
        }
    }
    return result;
}
struct Vector dotProductBufferedOMP(struct SquareMatrix m, struct Vector v, double *buffer) {
    const size_t size = v.size;
    #pragma omp parallel default(none) shared(m, v, buffer)
    {
        #pragma omp for
        for (size_t i = 0; i < size; ++i) {
            struct Vector row = getRow(m, i);
            buffer[i] = scalarComposition(row, v);
            freeVector(row);
        }
    }
}
