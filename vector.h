//
// Created by а on 14.12.2019.
//

#ifndef TEST_VECTOR_H
#define TEST_VECTOR_H

#include <stdio.h>
#include <stdlib.h>

struct Vector {
    int size;
    double *vector;
};

struct Vector initVector(int size);
void freeVector(struct Vector v);

void printVector(struct Vector v);

struct Vector readVectorFromStdIn();
#endif //TEST_VECTOR_H
