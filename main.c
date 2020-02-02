#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "vector.h"
#include "optimization.h"
#include "omp.h"
#include <time.h>

struct Vector minusGrad(struct Vector x, struct SquareMatrix hessian, struct Vector rightEqVector) {
    return multiplyVectorOnNumber(
            subtractVector(
                    dotProduct(hessian, x),
                    rightEqVector),
            -1);
}

void execute_ncgm() {
    int size = 0;
    scanf("%d", &size);
    struct SquareMatrix hessian = readMatrixFromStdInSized(size);

    struct Vector b = readVectorFromStdInSized(size);

    struct Vector xPredicted = optimizeFletcherReeves(hessian, b, minusGrad);
    printVector(xPredicted);

    freeMatrix(hessian);
    freeVector(b);
    freeVector(xPredicted);
}

int main() {
    int vsize = 10000;
    struct SquareMatrix A = eyeMatrix(vsize);
    struct Vector v = onesVector(vsize);
    struct Vector res;
    clock_t start, finish;

    start = clock();
    res = dotProductParallel(A, v);
    finish = clock();
    float parallel_time = (float) (finish - start) / CLOCKS_PER_SEC;
    printf("Parallel ime: %f\n", parallel_time);

    start = clock();
    res = dotProduct(A, v);
    finish = clock();
    float seq_time = (float) (finish - start) / CLOCKS_PER_SEC;
    printf("Sequental time: %f\n", seq_time);

    printf("Time coef: %f", seq_time / parallel_time);

    freeVector(res);
    freeVector(v);
    freeMatrix(A);

    return 0;
}
