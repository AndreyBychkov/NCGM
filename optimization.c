//
// Created by а on 14.12.2019.
//

#include "optimization.h"
#include "matrix.h"
#include "vector.h"
#include <float.h>


struct Vector optimizeFletcherReeves(struct SquareMatrix hessian,
                                     struct Vector rightEqVector,
                                     struct Vector (*minusGradient)(struct Vector, struct SquareMatrix,
                                                                    struct Vector)) {

    double minGradDifference = 1e-6;
    double gradDifference = DBL_MAX;

    double minXDifference = 1e-4;
    double xDifference = DBL_MAX;

    struct Vector x = initVector(rightEqVector.size);
    struct Vector previousX = zeroVector(x.size);
    struct Vector previousMinusGrad = minusGradient(previousX, hessian, rightEqVector);
    struct Vector previousBasisVector = copyVector(previousMinusGrad);

    int iterationCounter = 1;
    while (gradDifference > minGradDifference || xDifference > minXDifference) {
        struct Vector minusGrad = minusGradient(previousX, hessian, rightEqVector);
        double beta = scalarComposition(minusGrad, minusGrad) / scalarComposition(previousMinusGrad, previousMinusGrad);
        struct Vector basisVector = addVector(minusGrad, multiplyVectorOnNumber(previousBasisVector, beta));
        double alpha = scalarComposition(minusGrad, basisVector) /
                       (scalarComposition(basisVector, dotProduct(hessian, basisVector)));

        struct Vector xNew = addVector(previousX, multiplyVectorOnNumber(basisVector, alpha));
        copyToVector(xNew, x);
        freeVector(xNew);

        gradDifference = meanAbsoluteErrorVector(minusGrad, previousMinusGrad);
        xDifference = meanAbsoluteErrorVector(x, previousX);

        copyToVector(x, previousX);
        copyToVector(minusGrad, previousMinusGrad);
        copyToVector(basisVector, previousBasisVector);

        freeVector(previousMinusGrad);
        freeVector(basisVector);

        if (iterationCounter % 100 == 0) {
            printf("\rCurrent iteration: %d. X MAE: %.2lf. Gradient MAE: %.2lf",
                   iterationCounter, xDifference, gradDifference);
            fflush(stdout);
        }
        ++iterationCounter;
    }
    printf("\n");

    freeVector(previousX);
    return x;
}
