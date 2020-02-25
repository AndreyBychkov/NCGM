//
// Created by а on 26.02.2020.
//

#include <float.h>
#include "optimization_omp.h"
#include "matrix_omp.h"
#include "vector_omp.h"

struct Vector optimizeFletcherReevesOMP(struct SquareMatrix hessian,
                                        struct Vector rightEqVector,
                                        struct Vector (*minusGradient)
                                                (struct Vector, struct SquareMatrix, struct Vector)) {
    double minGradDifference = 1e-7;
    double gradDifference = DBL_MAX;

    double minXDifference = 1e-7;
    double xDifference = DBL_MAX;

    struct Vector x = zeroVector(rightEqVector.size);
    struct Vector xNew = initVector(x.size);
    struct Vector basisVector = initVector(x.size);
    struct Vector hessianBasisVector = initVector(x.size);
    struct Vector basisVectorAlpha = initVector(x.size);
    struct Vector previousX = zeroVector(x.size);
    struct Vector prevBasisVectorBeta = initVector(x.size);
    struct Vector previousMinusGrad = minusGradient(previousX, hessian, rightEqVector);
    struct Vector previousBasisVector = copyVector(previousMinusGrad);

    int iterationCounter = 0;
    while (xDifference > minXDifference && (gradDifference > minGradDifference || iterationCounter > 0)) {
        struct Vector minusGrad = minusGradient(previousX, hessian, rightEqVector);
        double beta = scalarComposition(minusGrad, minusGrad)
                    / scalarComposition(previousMinusGrad, previousMinusGrad);

        multiplyVectorOnNumberBuffered(previousBasisVector, beta, prevBasisVectorBeta.vector);
        addVectorBuffered(minusGrad, prevBasisVectorBeta, basisVector.vector);

        dotProductBufferedOMP(hessian, basisVector, hessianBasisVector.vector);
        double alpha = scalarComposition(minusGrad, basisVector) /
                       scalarComposition(hessianBasisVector, basisVector);

        multiplyVectorOnNumberBuffered(basisVector, alpha, basisVectorAlpha.vector);
        addVectorBuffered(previousX, basisVectorAlpha, xNew.vector);
        copyToVector(xNew, x);

        gradDifference = meanAbsoluteErrorVector(minusGrad, previousMinusGrad);
        xDifference = meanAbsoluteErrorVector(x, previousX);

        copyToVector(x, previousX);
        copyToVector(minusGrad, previousMinusGrad);
        copyToVector(basisVector, previousBasisVector);

        freeVector(minusGrad);

        ++iterationCounter;
    }

    freeVector(xNew);
    freeVector(previousX);
    freeVector(previousMinusGrad);
    freeVector(previousBasisVector);
    freeVector(prevBasisVectorBeta);
    freeVector(basisVectorAlpha);
    freeVector(hessianBasisVector);
    freeVector(basisVector);
    return x;
}
