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
            -2);
}

int main() {

    struct SquareMatrix hessian = randomMatrix(3);
    printMatrix(hessian);

    struct Vector xTrue = randomVector(3);
    printVector(xTrue);

    struct Vector b = dotProduct(hessian, xTrue);
    printVector(b);

    struct Vector xPredicted  = optimizeFletcherReeves(hessian, b, minusGrad);
    printVector(xPredicted);

    freeMatrix(hessian);
    freeVector(xTrue);
    freeVector(b);
    freeVector(xPredicted);

    return 0;
}
