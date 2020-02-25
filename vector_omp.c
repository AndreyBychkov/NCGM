//
// Created by а on 26.02.2020.
//

#include "vector_omp.h"

struct Vector zeroVectorOMP(size_t size) {
    struct Vector v = initVector(size);
    #pragma omp parallel default(none) shared(v, size)
    {
        #pragma omp for
        for (size_t i = 0; i < size; ++i) {
            v.vector[i] = 0.0;
        }
    }
    return v;
}
struct Vector onesVectorOMP(size_t size) {
    struct Vector v = initVector(size);
    #pragma omp parallel default(none) shared(v, size)
    {
        #pragma omp for
        for (size_t i = 0; i < size; ++i) {
            v.vector[i] = 1.0;
        }
    }
    return v;
}

struct Vector randomVectorOMP(size_t size) {
    struct Vector v = initVector(size);
    #pragma omp parallel default(none) shared(v, size)
    {
        #pragma omp for
        for (size_t i = 0; i < size; ++i) {
            v.vector[i] = rand() % 10;
        }
    }
    return v;
}

struct Vector copyVectorOMP(struct Vector v) {
    struct Vector result = initVector(v.size);
    #pragma omp parallel default(none) shared(v, result)
    {
        #pragma omp for
        for (size_t i = 0; i < v.size; ++i) {
            result.vector[i] = v.vector[i];
        }
    }
    return result;
}
void copyToVectorOMP(struct Vector from, struct Vector to) {
    #pragma omp parallel default(none) shared(from, to)
    {
        #pragma omp for
        for (size_t i = 0; i < from.size; ++i) {
            to.vector[i] = from.vector[i];
        }
    }
}

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

void addVectorBufferedOMP(struct Vector first, struct Vector second, double *buffer) {
    #pragma omp parallel default(none) shared(first, second, buffer)
    {
        #pragma omp for
        for (size_t i = 0; i < first.size; ++i) {
            buffer[i] = first.vector[i] + second.vector[i];
        }
    }
}
void subtractVectorBufferedOMP(struct Vector first, struct Vector second, double *buffer) {
    #pragma omp parallel default(none) shared(first, second, buffer)
    {
        #pragma omp for
        for (size_t i = 0; i < first.size; ++i) {
            buffer[i] = first.vector[i] - second.vector[i];
        }
    }
}
void multiplyVectorOnNumberBufferedOMP(struct Vector v, double factor, double *buffer) {
    #pragma omp parallel default(none) shared(v, factor, buffer)
    {
        #pragma omp for
        for (size_t i = 0; i < v.size; ++i) {
            buffer[i] = v.vector[i] * factor;
        }
    }
}
void divideVectorOnNumberBufferedOMP(struct Vector v, double divisor, double *buffer) {
    #pragma omp parallel default(none) shared(v, divisor, buffer)
    {
        #pragma omp for
        for (size_t i = 0; i < v.size; ++i) {
            buffer[i] = v.vector[i] / divisor;
        }
    }
}

double scalarCompositionOMP(struct Vector v1, struct Vector v2) {
    double result = 0;
    #pragma omp parallel default(none) shared(v1, v2, result)
    {
        #pragma omp for reduction(+:result)
        for (size_t i = 0; i < v1.size; ++i) {
            result += v1.vector[i] * v2.vector[i];
        }
    }
    return result;
}
