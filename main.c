#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "vector.h"
#include "optimization.h"
#include "optimization_omp.h"
#include "matrix_omp.h"
#include <time.h>
#include <mpi.h>

static struct Vector minusGrad(struct Vector x, struct SquareMatrix hessian, struct Vector rightEqVector) {
    struct Vector hessX = dotProduct(hessian, x);
    struct Vector diffVector = subtractVector(hessX, rightEqVector);
    struct Vector result =  minus(diffVector);

    freeVector(hessX);
    freeVector(diffVector);
    return result;
}

static struct Vector minusGradOMP(struct Vector x, struct SquareMatrix hessian, struct Vector rightEqVector) {
    struct Vector hessX = dotProductOMP(hessian, x);
    struct Vector diffVector = subtractVector(hessX, rightEqVector);
    struct Vector result =  minus(diffVector);

    freeVector(hessX);
    freeVector(diffVector);
    return result;
}

void stdInMain() {
    size_t size = 0;
    scanf("%d", &size);
    struct SquareMatrix hessian = readMatrixFromStdInSized(size);
    struct Vector b  = readVectorFromStdInSized(size);
    struct Vector xPredicted  = optimizeFletcherReevesOMP(hessian, b, minusGradOMP);
    printVectorPrecise(xPredicted);

    freeMatrix(hessian);
    freeVector(b);
    freeVector(xPredicted);
}

void multiply(double *A, double *B, double *C, int istart, int iend, size_t size)
{
    for (int i = istart; i <= iend; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                C[i*size + j] += A[i*size + k] * B[k*size + j];
            }
        }
    }
}

int main(int argc, char* argv[])
{
    int rank, procNum;
    int istart, iend;
    size_t size = 10;
    struct SquareMatrix A = eyeMatrix(size);
    struct SquareMatrix B = eyeMatrix(size);
    struct SquareMatrix C = initMatrix(size);
    struct SquareMatrix Ctemp = initMatrix(size);

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Bcast(A.matrix, size * size, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(B.matrix, size * size, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(C.matrix, size * size, MPI_FLOAT, 0, MPI_COMM_WORLD);

    istart = (size / procNum) * rank;
    iend = (size / procNum) * (rank + 1) - 1;

    multiply(A.matrix, B.matrix, C.matrix, istart, iend, size);

    // Gather computed results.
    MPI_Gather(C.matrix + (size / procNum * rank),
               size * size / procNum,
               MPI_FLOAT,
               Ctemp.matrix + (size / procNum * rank),
               size * size / procNum,
               MPI_FLOAT,
               0,
               MPI_COMM_WORLD);

    if (rank == 0) {
        // Compute remaining
        if (size % procNum > 0) {
            multiply(A.matrix, B.matrix, C.matrix, (size / procNum) * procNum, size - 1, size);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();

    if (rank == 0) {
        printMatrix(C);
    }

    return 0;
}
