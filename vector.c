//
// Created by а on 14.12.2019.
//

#include "vector.h"

struct Vector initVector(int size) {
    struct Vector v;
    v.size = size;
    v.vector = malloc(size * sizeof(*v.vector));

    return v;
}

void freeVector(struct Vector v) {
    free(v.vector);
}

void printVector(struct Vector v) {
    for (int i = 0; i < v.size; ++i) {
        printf("%lf ", v.vector[i]);
    }
    printf("\n");
}

static int readVectorSizeFromStdIn() {
    char sizeStr[5];
    fgets(sizeStr, sizeof(sizeStr), stdin);
    char *end;
    int size = strtol(sizeStr, &end, 10);

    return size;
}

static void read1DArrayFromStdIn(struct Vector v) {
    for (int i = 0; i < v.size; ++i) {
        scanf("%lf", &v.vector[i]);
    }
}

struct Vector readVectorFromStdIn() {
    int size = readVectorSizeFromStdIn();
    struct Vector v = initVector(size);
    read1DArrayFromStdIn(v);

    return v;
}

double scalarComposition(struct Vector v1, struct Vector v2) {
    double result = 0;
    for (int i = 0; i < v1.size; ++i) {
        result += v1.vector[i] * v2.vector[i];
    }
    return result;
}
