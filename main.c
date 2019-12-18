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

    struct SquareMatrix hessian = zeroMatrix(3);
    hessian.matrix[0][0] = 3;
    hessian.matrix[1][0] = 4;
    hessian.matrix[0][1] = 4;
    hessian.matrix[1][1] = -3;
    hessian.matrix[2][2] = 5;
    printMatrix(hessian);
    printf("\n");

    struct Vector b  = initVector(3);
    b.vector[0] = 1;
    b.vector[1] = 5;
    b.vector[2] =  9;
    printVector(b);
    printf("\n");

    struct Vector xPredicted  = optimizeFletcherReeves(hessian, b, minusGrad);
    printVector(xPredicted);

    struct Vector xTrueApprox = initVector(3);
    xTrueApprox.vector[0] = 0.92;
    xTrueApprox.vector[1] = -0.44;
    xTrueApprox.vector[2] = 1.8;

    printf("MAE for answer: %0.8lf.\n", meanAbsoluteErrorVector(xTrueApprox, xPredicted));

    freeMatrix(hessian);
    freeVector(b);
    freeVector(xPredicted);
    freeVector(xTrueApprox);

    return 0;
}
