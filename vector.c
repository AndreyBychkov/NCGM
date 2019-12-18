//
// Created by а on 14.12.2019.
//

#include "vector.h"
#include <math.h>

struct Vector initVector(int size) {
    struct Vector v;
    v.size = size;
    v.vector = malloc(size * sizeof(*v.vector));

    return v;
}

struct Vector zeroVector(int size) {
    struct Vector v = initVector(size);
    for (int i = 0; i < size; ++i) {
        v.vector[i] = 0.0;
    }
    return v;
}

struct Vector onesVector(int size) {
    struct Vector v = initVector(size);
    for (int i = 0; i < size; ++i) {
        v.vector[i] = 1.0;
    }
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

struct Vector addVector(struct Vector first, struct Vector second) {
    struct Vector result = initVector(first.size);
    for (int i = 0; i < first.size; ++i) {
        result.vector[i] = first.vector[i] + second.vector[i];
    }
    return result;
}

struct Vector subtractVector(struct Vector first, struct Vector second) {
    struct Vector result = initVector(first.size);
    for (int i = 0; i < first.size; ++i) {
        result.vector[i] = first.vector[i] - second.vector[i];
    }
    return result;
}

struct Vector multiplyVectorOnNumber(struct Vector v, double factor) {
    struct Vector result = initVector(v.size);
    for (int i = 0; i < v.size; ++i) {
        result.vector[i] = v.vector[i] * factor;
    }
    return result;
}

struct Vector divideVectorOnNumber(struct Vector v, double divisor) {
    struct Vector result = initVector(v.size);
    for (int i = 0; i < v.size; ++i) {
        result.vector[i] = v.vector[i] / divisor;
    }
    return result;
}

struct Vector minus(struct Vector v) {
    struct Vector result = initVector(v.size);
    for (int i = 0; i < v.size; ++i) {
        result.vector[i] = -v.vector[i];
    }
    return result;
}

void minusMutable(struct Vector v) {
    for (int i = 0; i < v.size; ++i) {
        v.vector[i] = -v.vector[i];
    }
}

void addVectorMutable(struct Vector changing, struct Vector another) {
    for (int i = 0; i < changing.size; ++i) {
        changing.vector[i] += another.vector[i];
    }
}

void subtractVectorMutable(struct Vector changing, struct Vector another) {
    for (int i = 0; i < changing.size; ++i) {
        changing.vector[i] -= another.vector[i];
    }
}

void multiplyVectorOnNumberMutable(struct Vector changing, double factor) {
    for (int i = 0; i < changing.size; ++i) {
        changing.vector[i] *= factor;
    }
}

void divideVectorOnNumberMutable(struct Vector changing, double divisor) {
    for (int i = 0; i < changing.size; ++i) {
        changing.vector[i] /= divisor;
    }
}

struct Vector copyVector(struct Vector v) {
    struct Vector result = initVector(v.size);
    for (int i = 0; i < v.size; ++i) {
        result.vector[i] = v.vector[i];
    }
    return result;
}

double meanAbsoluteErrorVector(struct Vector first, struct Vector second) {
    double result = 0;
    for (int i = 0; i < first.size; ++i) {
        result += fabs(first.vector[i] - second.vector[i]);
    }
    return result;
}

void copyToVector(struct Vector from, struct Vector to) {
    for (int i = 0; i < from.size; ++i) {
        to.vector[i] = from.vector[i];
    }
}

struct Vector randomVector(int size) {
    struct Vector v = initVector(size);
    for (int i = 0; i < size; ++i) {
        v.vector[i] = rand() % 10;
    }
    return v;
}




