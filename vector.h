//
// Created by а on 14.12.2019.
//

#ifndef TEST_VECTOR_H
#define TEST_VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Vector {
    size_t size;
    double *vector;
};

struct Vector initVector(size_t size);
struct Vector zeroVector(size_t size);
struct Vector onesVector(size_t size);
struct Vector randomVector(size_t size);
void freeVector(struct Vector v);

void printVector(struct Vector v);
void printVectorPrecise(struct Vector v);

struct Vector readVectorFromStdIn();
struct Vector readVectorFromStdInSized(size_t size);

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

void addVectorBuffered(struct Vector first, struct Vector second, double *buffer);
void subtractVectorBuffered(struct Vector first, struct Vector second, double *buffer);
void multiplyVectorOnNumberBuffered(struct Vector v, double factor, double *buffer);
void divideVectorOnNumberBuffered(struct Vector v, double divisor, double *buffer);

double meanAbsoluteErrorVector(struct Vector first, struct Vector second);

double scalarComposition(struct Vector v1, struct Vector v2);

#endif //TEST_VECTOR_H
