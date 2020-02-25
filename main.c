#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "vector.h"
#include "optimization.h"
#include "optimization_omp.h"
#include "matrix_omp.h"
#include <time.h>

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

void stdInMain() {
    size_t size = 0;
    scanf("%d", &size);
    struct SquareMatrix hessian = readMatrixFromStdInSized(size);

    struct Vector b  = readVectorFromStdInSized(size);

    struct Vector xPredicted  = optimizeFletcherReevesOMP(hessian, b, minusGradOMP);
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

int main() {
    stdInMain();

    return 0;
}
