#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"
#include "vector.h"
#include "optimization.h"
#include "optimization_omp.h"
#include "matrix_omp.h"
#include "optimization_mpi.h"
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

static struct Vector minusGradMPI(struct Vector x, struct SquareMatrix hessian, struct Vector rightEqVector) {
    struct Vector hessX = dotProductMPI(hessian, x);
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

void stdInMPIMain(int argc, char* argv[]) {
    int rank, procNum;
    int size;
    struct SquareMatrix hessian;
    struct Vector b, xPredicted;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        scanf("%d", &size);
        hessian = readMatrixFromStdInSized(size);
        b  = readVectorFromStdInSized(size);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    xPredicted = optimizeFletcherReevesMPI(hessian, b, minusGradMPI);

    if (rank == 0) {
        printVectorPrecise(xPredicted);
        freeMatrix(hessian);
        freeVector(b);
        freeVector(xPredicted);
    }

    MPI_Finalize();
}

void testMPIMain(int argc, char* argv[]) {
    int rank, procNum;
    int size = 900;
    struct SquareMatrix hessian;
    struct Vector b, xPredicted;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        hessian = randomSymmetricMatrix(size);
        b  = randomVector(size);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    xPredicted = optimizeFletcherReevesMPI(hessian, b, minusGradMPI);

    if (rank == 0) {
        freeMatrix(hessian);
        freeVector(b);
        freeVector(xPredicted);
    }

    MPI_Finalize();
}

void testMatMulMPI(int argc, char* argv[]) {
    int rank, procNum;
    int size = 900;
    struct SquareMatrix A;
    struct Vector b, res;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        A = randomSymmetricMatrix(size);
        b = randomVector(size);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    dotProductMPIBuffered(A, b, res.vector);

    if (rank == 0) {
        freeMatrix(A);
        freeVector(b);
        freeVector(res);
    }

    MPI_Finalize();
}

int main(int argc, char* argv[])
{
    testMatMulMPI(argc, argv);
    return 0;
}
