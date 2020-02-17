//
// Created by а on 14.12.2019.
//
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

struct SquareMatrix initMatrix(size_t size) {
    struct SquareMatrix m;
    m.size = size;
    m.matrix = malloc(size * size * sizeof(double));
    return m;
}

struct SquareMatrix zeroMatrix(size_t size) {
    struct SquareMatrix m = initMatrix(size);
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            m.matrix[m.size * i + j] = 0.0;
        }
    }
    return m;
}

struct SquareMatrix eyeMatrix(size_t size) {
    struct SquareMatrix m = zeroMatrix(size);
    for (size_t i = 0; i < size; ++i) {
        m.matrix[m.size * i + i] = 1.0;
    }
    return m;
}

struct SquareMatrix randomMatrix(size_t size) {
    struct SquareMatrix m = initMatrix(size);
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            m.matrix[m.size * i + j] = rand() % 10;
        }
    }
    return m;
}

void freeMatrix(struct SquareMatrix m) {
    free(m.matrix);
}

void printMatrix(struct SquareMatrix m) {
    for (size_t i = 0; i != m.size; ++i) {
        for (size_t j = 0; j != m.size; ++j) {
            printf("%f ", m.matrix[m.size * i + j]);
        }
        printf("\n");
    }
}

static size_t readMatrixSizeFromStdIn() {
    char sizeStr[5];
    fgets(sizeStr, sizeof(sizeStr), stdin);
    char *end;
    long size = strtol(sizeStr, &end, 10);

    if (size >= 0) {
        return (size_t) size;
    } else {
        fprintf(stderr, "%s", "Failed to read matrix from stdin.\n");
        exit(EXIT_FAILURE);
    }
}

static void read2DArrayFromStdIn(struct SquareMatrix m) {
    for (size_t i = 0; i < m.size; ++i) {
        for (size_t j = 0; j < m.size; ++j) {
            scanf("%lf", &m.matrix[m.size * i + j]);
        }
    }
}

struct SquareMatrix readMatrixFromStdIn() {
    size_t size = readMatrixSizeFromStdIn();
    struct SquareMatrix m = initMatrix(size);
    read2DArrayFromStdIn(m);

    return m;
}

struct SquareMatrix readMatrixFromStdInSized(size_t size) {
    struct SquareMatrix m = initMatrix(size);
    read2DArrayFromStdIn(m);

    return m;
}

struct SquareMatrix copyMatrix(struct SquareMatrix m) {
    struct SquareMatrix result = initMatrix(m.size);
    for (size_t i = 0; i < m.size; ++i) {
        for (size_t j = 0; j < m.size; ++j) {
            result.matrix[m.size * i + j] = m.matrix[m.size * i + j];
        }
    }
    return result;
}

void copyToMatrix(struct SquareMatrix from, struct SquareMatrix to) {
    for (size_t i = 0; i < from.size; ++i) {
        for (size_t j = 0; j < from.size; ++j) {
            to.matrix[to.size * i + j] = from.matrix[from.size * i + j];
        }
    }
}

struct Vector getColumn(struct SquareMatrix m, size_t index) {
    struct Vector v = initVector(m.size);
    for (size_t i = 0; i < m.size; ++i) {
        v.vector[i] = m.matrix[m.size * i + index];
    }
    return v;
}

struct Vector getRow(struct SquareMatrix m, size_t index) {
    struct Vector v = initVector(m.size);
    for (size_t j = 0; j < m.size; ++j) {
        v.vector[j] = m.matrix[m.size * index + j];
    }
    return v;
}

void getColumnBuffered(struct SquareMatrix m, size_t index, double *buffer) {
    for (size_t i = 0; i < m.size; ++i) {
        buffer[i] = m.matrix[m.size * i + index];
    }
}

void getRowBuffered(struct SquareMatrix m, size_t index, double *buffer) {
    for (size_t j = 0; j < m.size; ++j) {
        buffer[j] = m.matrix[m.size * index + j];
    }
}

struct Vector dotProduct(struct SquareMatrix m, struct Vector v) {
    struct Vector result = initVector(v.size);
    struct Vector bufferVector = initVector(v.size);

    for (size_t i = 0; i < v.size; ++i) {
        getRowBuffered(m, i, bufferVector.vector);
        result.vector[i] = scalarComposition(bufferVector, v);
    }

    return result;
}

void dotProductBuffered(struct SquareMatrix m, struct Vector v, double *buffer) {
    struct Vector bufferVector = initVector(v.size);

    for (size_t i = 0; i < v.size; ++i) {
        getRowBuffered(m, i, bufferVector.vector);
        buffer[i] = scalarComposition(bufferVector, v);
    }
}



