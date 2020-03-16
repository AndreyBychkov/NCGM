//
// Created by а on 16.03.2020.
//

#include "matrix_mpi.h"

void multiply(double *matrix, double *vector, double *result_vector, int istart, int iend, size_t size) {
    for (size_t i = istart; i <= iend; ++i) {
        for (size_t j = 0; j < size; ++j) {
            result_vector[i] += matrix[i * size + j] * vector[i];
        }
    }
}

struct Vector dotProductMPI(struct SquareMatrix m, struct Vector v) {
    const size_t size = m.size;
    struct Vector result = initVector(size);
    struct Vector resultTemp = initVector(size);

    int rank, procNum;
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Bcast(m.matrix, size * size, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(v.vector, size, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(result.vector, size, MPI_FLOAT, 0, MPI_COMM_WORLD);

    int istart = (size / procNum) * rank;
    int iend = (size / procNum) * (rank + 1) - 1;

    multiply(m.matrix, v.vector, result.vector, istart, iend, size);

    MPI_Gather(result.vector + (size / procNum * rank),
               size / procNum,
               MPI_FLOAT,
               resultTemp.vector + (size / procNum * rank),
               size / procNum,
               MPI_FLOAT,
               0,
               MPI_COMM_WORLD);

    if (rank == 0) {
        // Compute remaining
        if (size % procNum > 0) {
            multiply(m.matrix, v.vector, result.vector, (size / procNum) * procNum, size - 1, size);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    return result;
}