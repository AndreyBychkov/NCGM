#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "vector.h"
#include "optimization.h"
#include "optimization_omp.h"
#include "matrix_omp.h"
#include <time.h>

struct Vector minusGrad(struct Vector x, struct SquareMatrix hessian, struct Vector rightEqVector) {
    return multiplyVectorOnNumber(
            subtractVector(
                    dotProduct(hessian, x),
                    rightEqVector),
            -1);
}

void stdInMain() {
    size_t size = 0;
    scanf("%d", &size);
    struct SquareMatrix hessian = readMatrixFromStdInSized(size);

    struct Vector b  = readVectorFromStdInSized(size);

    struct Vector xPredicted  = optimizeFletcherReeves(hessian, b, minusGrad);
    printVector(xPredicted);

    freeMatrix(hessian);
    freeVector(b);
    freeVector(xPredicted);
}

void dotProductExecutionCompareMain() {
    size_t size = 10000;
    struct SquareMatrix m = randomMatrixOMP(size);
    struct Vector v = randomVector(size);
    struct Vector res = initVector(size);
    struct Vector resParallel = initVector(size);
    clock_t start, finish;

    start = clock();
    dotProductBuffered(m, v, res.vector);
    finish = clock();
    float seq_time = (float) (finish - start) / CLOCKS_PER_SEC;
    printf("Sequential time: %f\n", seq_time);

    start = clock();
//    dotProductBufferedOMP(m, v, resParallel.vector);
    resParallel = dotProductOMP(m, v);
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

    freeMatrix(m);
    freeVector(v);
    freeVector(res);
    freeVector(resParallel);
}

void optimizationFletcherReevesExecutionCompareMain() {
    size_t size = 200;
    struct SquareMatrix m = randomSymmetricMatrixOMP(size);
    struct Vector v = randomVector(size);
    struct Vector res = initVector(size);
    struct Vector resParallel = initVector(size);
    clock_t start, finish;

    start = clock();
    res = optimizeFletcherReevesOMP(m, v, minusGrad);
    finish = clock();
    float seq_time = (float) (finish - start) / CLOCKS_PER_SEC;
    printf("Sequential time: %f\n", seq_time);

    start = clock();
    resParallel = optimizeFletcherReevesOMP(m, v, minusGrad);
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

    freeMatrix(m);
    freeVector(v);
    freeVector(res);
    freeVector(resParallel);
}

int main() {
    optimizationFletcherReevesExecutionCompareMain();

    return 0;
}
