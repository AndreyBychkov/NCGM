//
// Created by а on 16.03.2020.
//

#include "matrix_mpi.h"

struct Vector dotProductMPI(struct SquareMatrix m, struct Vector v) {
    int rank, procNum;
    size_t size = v.size;
    struct Vector result = initVector(size);

    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    size_t numRowsEach = size / procNum;
    size_t numItemsEach = size * numRowsEach;
    double *subResultBuf = (double*)malloc(sizeof(double) * numRowsEach);
    double *subMatrix = (double*)malloc(sizeof(double) * numItemsEach);

    MPI_Bcast(v.vector, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(m.matrix, numItemsEach, MPI_DOUBLE, subMatrix, numItemsEach, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int i = 0; i != numRowsEach; ++i) {
        subResultBuf[i] = 0;
        for (int j = 0; j != size; ++j) {
            subResultBuf[i] += subMatrix[i * numRowsEach +  j] * v.vector[j];
        }
    }


    MPI_Gather(subResultBuf, numRowsEach, MPI_DOUBLE, result.vector, numRowsEach, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    free(subMatrix);
    free(subResultBuf);

    return result;
}