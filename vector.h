//
// Created by а on 14.12.2019.
//

#ifndef TEST_VECTOR_H
#define TEST_VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Vector {
    int size;
    double *vector;
};

struct Vector initVector(int size);
struct Vector zeroVector(int size);
struct Vector onesVector(int size);
void freeVector(struct Vector v);

void printVector(struct Vector v);

struct Vector readVectorFromStdIn();
struct Vector readVectorFromStdInSized(int size);

struct Vector copyVector(struct Vector v);
void copyToVector(struct Vector from, struct Vector to);

struct Vector minus(struct Vector v);
void minusMutable(struct Vector v);

bool equalsVector(struct Vector first, struct Vector second);

struct Vector addVector(struct Vector first, struct Vector second);
struct Vector subtractVector(struct Vector first, struct Vector second);
struct Vector multiplyVectorOnNumber(struct Vector v, double factor);
struct Vector divideVectorOnNumber(struct Vector v, double divisor);

void addVectorMutable(struct Vector changing, struct Vector another);
void subtractVectorMutable(struct Vector changing, struct Vector another);
void multiplyVectorOnNumberMutable(struct Vector changing, double factor);
void divideVectorOnNumberMutable(struct Vector changing, double divisor);

double meanAbsoluteErrorVector(struct Vector first, struct Vector second);

struct Vector randomVector(int size);

double scalarComposition(struct Vector v1, struct Vector v2);

#endif //TEST_VECTOR_H
