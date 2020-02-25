//
// Created by а on 18.12.2019.
//

#include "optimizations_tests.h"
#include "../matrix.h"
#include "../vector.h"
#include "../optimization.h"

static struct Vector minusGrad(struct Vector x, struct SquareMatrix hessian, struct Vector rightEqVector) {
    return multiplyVectorOnNumber(
            subtractVector(
                    dotProduct(hessian, x),
                    rightEqVector),
            -1);
}

void testFletcherReevesDefault() {
    struct SquareMatrix hessian = zeroMatrix(3);
    hessian.matrix[hessian.size * 0 + 0] = 3;
    hessian.matrix[hessian.size * 1 + 0] = 4;
    hessian.matrix[hessian.size * 0 + 1] = 4;
    hessian.matrix[hessian.size * 1 + 1] = -3;
    hessian.matrix[hessian.size * 2 + 2] = 5;

    struct Vector b = initVector(3);
    b.vector[0] = 1;
    b.vector[1] = 5;
    b.vector[2] = 9;

    struct Vector xPredicted = optimizeFletcherReeves(hessian, b, minusGrad);

    struct Vector xTrueApprox = initVector(3);
    xTrueApprox.vector[0] = 0.92;
    xTrueApprox.vector[1] = -0.44;
    xTrueApprox.vector[2] = 1.8;

    double score = meanAbsoluteErrorVector(xTrueApprox, xPredicted);
    if (score < 1e-6) {
        printf("testFletcherReevesDefault: PASSED. \n");
    }
    else {
        printf("testFletcherReevesDefault: FAILED. \n");
    }

    freeMatrix(hessian);
    freeVector(b);
    freeVector(xPredicted);
    freeVector(xTrueApprox);
}

void optimizationTestSuite() {
    for (size_t i = 0; i < 40; ++i) putchar('-');
    printf("\nOptimization tests:\n\n");
    testFletcherReevesDefault();
}
