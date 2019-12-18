#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "vector.h"
#include "optimization.h"

struct Vector minusGrad(struct Vector x, struct SquareMatrix hessian, struct Vector rightEqVector) {
    return multiplyVectorOnNumber(
            subtractVector(
                    dotProduct(hessian, x),
                    rightEqVector),
            -1);
}

int main() {

    struct SquareMatrix hessian = readMatrixFromStdIn();
    printMatrix(hessian);
    printf("\n");

    struct Vector b  = readVectorFromStdIn();
    printVector(b);
    printf("\n");

    struct Vector xPredicted  = optimizeFletcherReeves(hessian, b, minusGrad);
    printVector(xPredicted);

    freeMatrix(hessian);
    freeVector(b);
    freeVector(xPredicted);

    return 0;
}
