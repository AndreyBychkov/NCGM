//
// Created by а on 26.02.2020.
//

#ifndef NCGM_OPTIMIZATION_OMP_H
#define NCGM_OPTIMIZATION_OMP_H

#include "vector.h"
#include "matrix.h"

struct Vector optimizeFletcherReevesOMP(struct SquareMatrix hessian,
                                        struct Vector rightEqVector,
                                        struct Vector (*minusGradient)(struct Vector, struct SquareMatrix, struct Vector));

#endif //NCGM_OPTIMIZATION_OMP_H
