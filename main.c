#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "vector.h"
#include "optimization.h"
#include "optimization_omp.h"
#include "matrix_omp.h"
#include <time.h>
#include <mpi.h>
#include "matrix_mpi.h"

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

int main(int argc, char* argv[])
{
    int rank, procNum;
    size_t size = 10;
    struct SquareMatrix m = eyeMatrix(size);
    struct Vector v = onesVector(size);
    struct Vector res;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   res = dotProductMPI(m, v);

    MPI_Finalize();

    if (rank == 0) {
        printVector(res);
    }

    return 0;
}
