//
// Created by а on 23.03.2020.
//

#ifndef NCGM_OPTIMIZATION_MPI_H
#define NCGM_OPTIMIZATION_MPI_H

#include "vector.h"
#include "matrix.h"
#include "matrix_mpi.h"

struct Vector optimizeFletcherReevesMPI(struct SquareMatrix hessian,
                                        struct Vector rightEqVector,
                                        struct Vector (*minusGradient)(struct Vector, struct SquareMatrix, struct Vector));

#endif //NCGM_OPTIMIZATION_MPI_H
