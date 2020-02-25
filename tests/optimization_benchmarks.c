//
// Created by а on 26.02.2020.
//

#include "optimization_benchmarks.h"
#include "../optimization.h"
#include "../optimization_omp.h"
#include "time.h"
#include "../matrix_omp.h"
#include "../vector_omp.h"

static struct Vector minusGrad(struct Vector x, struct SquareMatrix hessian, struct Vector rightEqVector) {
    struct Vector hessX = dotProduct(hessian, x);
    struct Vector diffVector = subtractVector(hessX, rightEqVector);
    struct Vector result =  minus(diffVector);

    freeVector(hessX);
    freeVector(diffVector);
    return result;
}

static struct Vector minusGradOMP(struct Vector x, struct SquareMatrix hessian, struct Vector rightEqVector) {
    struct Vector hessX = dotProductOMP(hessian, x);
    struct Vector diffVector = subtractVector(hessX, rightEqVector);
    struct Vector result =  minus(diffVector);

    freeVector(hessX);
    freeVector(diffVector);
    return result;
}

void fletcherReevesOMPBenchmark() {
    size_t size = 500;
    struct SquareMatrix hess = randomSymmetricMatrixOMP(size);
    struct Vector v = randomVector(size);
    struct Vector res = initVector(size);
    struct Vector resParallel = initVector(size);
    clock_t start, finish;

    printf("fletcherReevesOMPBenchmark:\n");

    start = clock();
    res = optimizeFletcherReeves(hess, v, minusGrad);
    finish = clock();
    float seq_time = (float) (finish - start) / CLOCKS_PER_SEC;
    printf("Sequential time: %f\n", seq_time);

    start = clock();
    resParallel = optimizeFletcherReevesOMP(hess, v, minusGradOMP);
    finish = clock();
    float parallel_time = (float) (finish - start) / CLOCKS_PER_SEC;
    printf("Parallel time: %f\n", parallel_time);

    printf("Time coef: %f\n", seq_time / parallel_time);

    bool isResEqual = equalsVector(res, resParallel);
    if (!isResEqual) {
        printf("Results are not equal!");
        printVector(res);
        printVector(resParallel);
    }

    freeMatrix(hess);
    freeVector(v);
    freeVector(res);
    freeVector(resParallel);
}

void optimizationBenchmarkSuite() {
    for (size_t i = 0; i < 40; ++i) putchar('-');
    printf("\nOptimization benchmarks:\n\n");

    fletcherReevesOMPBenchmark();
}
