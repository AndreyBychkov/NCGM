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

void predefinedMain() {
    size_t size = 10000;
    struct SquareMatrix m = eyeMatrix(size);
    struct Vector v = randomVector(size);

    struct Vector res = dotProduct(m, v);

    freeMatrix(m);
    freeVector(v);
    freeVector(res);
}

int main() {
    predefinedMain();

    return 0;
}
