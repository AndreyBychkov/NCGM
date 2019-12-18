//
// Created by а on 14.12.2019.
//

#include "optimization.h"
#include "matrix.h"
#include "vector.h"
#include <float.h>
#include <math.h>


struct Vector optimizeFletcherReeves(struct SquareMatrix hessian,
                                     struct Vector rightEqVector,
                                     struct Vector (*minusGradient)(struct Vector, struct SquareMatrix,
                                                                    struct Vector)) {

    double minGradDifference = 1e-7;
    double gradDifference = DBL_MAX;

    double minXDifference = 1e-7;
    double xDifference = DBL_MAX;

    struct Vector x = zeroVector(rightEqVector.size);
    struct Vector previousX = zeroVector(x.size);
    struct Vector previousMinusGrad = minusGradient(previousX, hessian, rightEqVector);
    struct Vector previousBasisVector = copyVector(previousMinusGrad);

    int iterationCounter = 0;
    while (xDifference > minXDifference && (gradDifference > minGradDifference || iterationCounter > 0)) {
        struct Vector minusGrad = minusGradient(previousX, hessian, rightEqVector);
        double beta = scalarComposition(minusGrad, minusGrad) / scalarComposition(previousMinusGrad, previousMinusGrad);
        struct Vector basisVector = addVector(minusGrad, multiplyVectorOnNumber(previousBasisVector, beta));
        double alpha = scalarComposition(minusGrad, basisVector) /
                       scalarComposition(dotProduct(hessian, basisVector), basisVector);

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

//        if (iterationCounter % 10 == 0) {
//            printf("\rCurrent iteration: %d. X MAE: %.7lf. Gradient MAE: %.7lf",
//                   iterationCounter, xDifference, gradDifference);
//            fflush(stdout);
//        }
        ++iterationCounter;
    }

//    printf("\nIterations passed: %d. \n", iterationCounter);

//    freeVector(previousX); TODO(Probably bug with memory here)
    return x;
}
