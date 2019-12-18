//
// Created by а on 14.12.2019.
//

#ifndef TEST_OPTIMIZATION_H
#define TEST_OPTIMIZATION_H

#include "vector.h"
#include "matrix.h"

struct Vector optimizeFletcherReeves(struct SquareMatrix hessian,
                                     struct Vector rightEqVector,
                                     struct Vector (*minusGradient)(struct Vector, struct SquareMatrix, struct Vector));
#endif //TEST_OPTIMIZATION_H
