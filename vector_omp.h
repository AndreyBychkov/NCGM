//
// Created by а on 26.02.2020.
//

#ifndef NCGM_VECTOR_OMP_H
#define NCGM_VECTOR_OMP_H

#include "vector.h"

struct Vector zeroVectorOMP(size_t size);
struct Vector onesVectorOMP(size_t size);
struct Vector randomVectorOMP(size_t size);

struct Vector copyVectorOMP(struct Vector v);
void copyToVectorOMP(struct Vector from, struct Vector to);

struct Vector minusOMP(struct Vector v);
void minusMutableOMP(struct Vector v);

struct Vector addVectorOMP(struct Vector first, struct Vector second);
struct Vector subtractVectorOMP(struct Vector first, struct Vector second);
struct Vector multiplyVectorOnNumberOMP(struct Vector v, double factor);
struct Vector divideVectorOnNumberOMP(struct Vector v, double divisor);

void addVectorMutableOMP(struct Vector changing, struct Vector another);
void subtractVectorMutableOMP(struct Vector changing, struct Vector another);
void multiplyVectorOnNumberMutableOMP(struct Vector changing, double factor);
void divideVectorOnNumberMutableOMP(struct Vector changing, double divisor);

void addVectorBufferedOMP(struct Vector first, struct Vector second, double *buffer);
void subtractVectorBufferedOMP(struct Vector first, struct Vector second, double *buffer);
void multiplyVectorOnNumberBufferedOMP(struct Vector v, double factor, double *buffer);
void divideVectorOnNumberBufferedOMP(struct Vector v, double divisor, double *buffer);

double scalarCompositionOMP(struct Vector v1, struct Vector v2);


#endif //NCGM_VECTOR_OMP_H
