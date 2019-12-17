//
// Created by а on 14.12.2019.
//
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

struct SquareMatrix initMatrix(int size) {
    struct SquareMatrix m;
    m.size = size;
    m.matrix = malloc(size * sizeof(*m.matrix));
    for (int i = 0; i != size; ++i) {
        m.matrix[i] = malloc(size * sizeof(*m.matrix[i]));
    }
    return m;
}

void freeMatrix(struct SquareMatrix m) {
    for (int i = 0; i < m.size; ++i) {
        free(m.matrix[i]);
    }
    free(m.matrix);
}

void printMatrix(struct SquareMatrix m) {
    for (int i = 0; i != m.size; ++i) {
        for (int j = 0; j != m.size; ++j) {
            printf("%f ", m.matrix[i][j]);
        }
        printf("\n");
    }
}

static int readMatrixSizeFromStdIn() {
    char sizeStr[5];
    fgets(sizeStr, sizeof(sizeStr), stdin);
    char *end;
    int size = strtol(sizeStr, &end, 10);

    return size;
}

static void read2DArrayFromStdIn(struct SquareMatrix m) {
    for (int i = 0; i < m.size; ++i) {
        for (int j = 0; j < m.size; ++j) {
            scanf("%lf", &m.matrix[i][j]);
        }
    }
}

struct SquareMatrix readMatrixFromStdIn() {
    int size = readMatrixSizeFromStdIn();
    struct SquareMatrix m = initMatrix(size);
    read2DArrayFromStdIn(m);

    return m;
}

struct SquareMatrix copyMatrix(struct SquareMatrix m) {
    struct SquareMatrix result = initMatrix(m.size);
    for (int i = 0; i < m.size; ++i) {
        for (int j = 0; j < m.size; ++j) {
            result.matrix[i][j] = m.matrix[i][j];
        }
    }
    return result;
}

void copyToMatrix(struct SquareMatrix from, struct SquareMatrix to) {
    for (int i = 0; i < from.size; ++i) {
        for (int j = 0; j < from.size; ++j) {
            to.matrix[i][j] = from.matrix[i][j];
        }
    }
}

struct Vector getColumn(struct SquareMatrix m, int index) {
    struct Vector v = initVector(m.size);
    for (int i = 0; i < m.size; ++i) {
        v.vector[i] = m.matrix[i][index];
    }
    return v;
}

struct Vector getRow(struct SquareMatrix m, int index) {
    struct Vector v = initVector(m.size);
    for (int i = 0; i < m.size; ++i) {
        v.vector[i] = m.matrix[index][i];
    }
    return v;
}

struct Vector dotProduct(struct SquareMatrix m, struct Vector v) {
    struct Vector result = initVector(v.size);

    for (int i = 0; i < v.size; ++i) {
        result.vector[i] = scalarComposition(getRow(m, i), v);
    }

    return result;
}

struct SquareMatrix zeroMatrix(int size) {
    struct SquareMatrix m = initMatrix(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            m.matrix[i][j] = 0.0;
        }
    }
    return m;
}

struct SquareMatrix eyeMatrix(int size) {
    struct SquareMatrix m = zeroMatrix(size);
    for (int i = 0; i < size; ++i) {
        m.matrix[i][i] = 1.0;
    }
    return m;
}



