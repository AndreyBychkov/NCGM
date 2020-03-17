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
    size_t size = 1200;
    struct SquareMatrix m = eyeMatrix(size);
    struct Vector v = onesVector(size);
    struct Vector result = initVector(size);

    MPI_Init(&argc, &argv);
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

    MPI_Finalize();

    if (rank == 0) {
        if (!equalsVector(v, result)) {
            printf("Vectors are not equal!\n");
            printVector(v);
            printVector(result);
        }

        freeMatrix(m);
        freeVector(v);
        freeVector(result);
    }

    return 0;
}
