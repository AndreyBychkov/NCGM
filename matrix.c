//
// Created by а on 14.12.2019.
//
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

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

struct SquareMatrix readFromStdIn() {
    int size = readMatrixSizeFromStdIn();
    struct SquareMatrix m = initMatrix(size);
    read2DArrayFromStdIn(m);

    return m;
}


