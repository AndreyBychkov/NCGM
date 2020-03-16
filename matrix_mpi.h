
#ifndef NCGM_MATRIX_MPI_H
#define NCGM_MATRIX_MPI_H

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "matrix.h"

struct Vector dotProductMPI(struct SquareMatrix m, struct Vector v);

#endif //NCGM_MATRIX_MPI_H
