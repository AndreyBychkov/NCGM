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

        struct Vector prevBasisVectorBeta = multiplyVectorOnNumber(previousBasisVector, beta);
        struct Vector basisVector = addVector(minusGrad, prevBasisVectorBeta);

        struct Vector hessianBasisVector = dotProduct(hessian, basisVector);
        double alpha = scalarComposition(minusGrad, basisVector) /
                       scalarComposition(hessianBasisVector, basisVector);

        struct Vector basisVectorAlpha = multiplyVectorOnNumber(basisVector, alpha);
        struct Vector xNew = addVector(previousX, basisVectorAlpha);
        copyToVector(xNew, x);


        gradDifference = meanAbsoluteErrorVector(minusGrad, previousMinusGrad);
        xDifference = meanAbsoluteErrorVector(x, previousX);

        copyToVector(x, previousX);
        copyToVector(minusGrad, previousMinusGrad);
        copyToVector(basisVector, previousBasisVector);

        freeVector(xNew);
        freeVector(minusGrad);
        freeVector(prevBasisVectorBeta);
        freeVector(basisVectorAlpha);
        freeVector(hessianBasisVector);
        freeVector(basisVector);

//        if (iterationCounter % 10 == 0) {
//            printf("\rCurrent iteration: %d. X MAE: %.7lf. Gradient MAE: %.7lf",
//                   iterationCounter, xDifference, gradDifference);
//            fflush(stdout);
//        }
//        ++iterationCounter;
    }

//    printf("\nIterations passed: %d. \n", iterationCounter);

    freeVector(previousX);
    freeVector(previousMinusGrad);
    freeVector(previousBasisVector);
    return x;
}
