#include <stdio.h>
#include <math.h>
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
    int size = 9000;
    struct SquareMatrix m;
    struct Vector v;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Status status;
    MPI_Request request;
    size_t sqrtProcNum = (size_t) sqrt(procNum);
    int blockSize = (int) ((double) size / sqrtProcNum);

    struct Vector vectorPart = initVector(blockSize);
    struct Vector resBlock = zeroVector(blockSize);
    struct Vector resBuf = zeroVector(blockSize);
    struct Vector res = initVector(size);

    double *matSubBlockOut = (double *) malloc(blockSize * size * sizeof(double));
    double *matSubBlockIn = (double *) malloc(((size * size) / procNum) * sizeof(double));


    // Define vector types
    MPI_Datatype MPI_MAT, MPI_VEC, MPI_BLOCK;
    MPI_Type_contiguous(blockSize * size, MPI_DOUBLE, &MPI_MAT);
    MPI_Type_contiguous(blockSize, MPI_DOUBLE, &MPI_VEC);
    MPI_Type_vector(blockSize, blockSize, size, MPI_DOUBLE, &MPI_BLOCK);
    MPI_Type_commit(&MPI_MAT);
    MPI_Type_commit(&MPI_VEC);
    MPI_Type_commit(&MPI_BLOCK);

    if (rank == 0) {
        m = eyeMatrix(size);
        v = randomVector(size);
    }

    // Make cartesian virtual grid topology
    MPI_Comm MPI_COMM_CART;
    int cartRank;
    size_t gridDimsNum = 2;
    int gridCoord[gridDimsNum];
    int gridDims[gridDimsNum];
    gridDims[0] = sqrtProcNum;
    gridDims[1] = sqrtProcNum;
    int gridPeriods[gridDimsNum];
    gridPeriods[0] = true;
    gridPeriods[1] = false;
    bool shouldGridReorder = true;
    MPI_Cart_create(MPI_COMM_WORLD, gridDimsNum, gridDims, gridPeriods, shouldGridReorder, &MPI_COMM_CART);
    MPI_Cart_coords(MPI_COMM_CART, rank, gridDimsNum, gridCoord);
    MPI_Cart_rank(MPI_COMM_CART, gridCoord, &cartRank);

    MPI_Comm MPI_COMM_CART_ROW, MPI_COMM_CART_COL;
    int gridBelongs[gridDimsNum];

    int rowRank;
    gridBelongs[0] = false;
    gridBelongs[1] = true;
    MPI_Cart_sub(MPI_COMM_CART, gridBelongs, &MPI_COMM_CART_ROW);
    MPI_Comm_rank(MPI_COMM_CART_ROW, &rowRank);

    int colRank;
    gridBelongs[0] = true;
    gridBelongs[1] = false;
    MPI_Cart_sub(MPI_COMM_CART, gridBelongs, &MPI_COMM_CART_COL);
    MPI_Comm_rank(MPI_COMM_CART_COL, &colRank);

    if (rowRank == 0)
        MPI_Scatter(m.matrix, 1, MPI_MAT, matSubBlockOut, blockSize * size, MPI_DOUBLE, 0, MPI_COMM_CART_COL);
    if (colRank == 0)
        MPI_Scatter(v.vector, 1, MPI_VEC, vectorPart.vector, blockSize, MPI_DOUBLE, 0, MPI_COMM_CART_ROW);

    MPI_Bcast(vectorPart.vector, blockSize, MPI_DOUBLE, 0, MPI_COMM_CART_COL);

    if (rowRank == 0)
        for (size_t i = 0l; i != sqrtProcNum; ++i)
            MPI_Isend(&matSubBlockOut[i * blockSize], 1, MPI_BLOCK, i, i, MPI_COMM_CART_ROW, &request);

    if (rowRank >= 0)
        MPI_Recv(matSubBlockIn, ((size * size) / procNum), MPI_DOUBLE, 0, rowRank, MPI_COMM_CART_ROW, &status);

    for (size_t i = 0; i != blockSize; ++i) {
        for (size_t j = 0; j != blockSize; ++j) {
            resBlock.vector[i] += matSubBlockIn[i * blockSize + j] * vectorPart.vector[i];
        }
    }

    MPI_Reduce(resBlock.vector, resBuf.vector, blockSize, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_CART_ROW);

    if (rowRank == 0)
        MPI_Gather(resBuf.vector, blockSize, MPI_DOUBLE, res.vector, blockSize, MPI_DOUBLE, 0, MPI_COMM_CART_COL);

    if (cartRank == 0) {
        printf("MAE: %lf\n", meanAbsoluteErrorVector(res, v));
    }

    MPI_Finalize();

    return 0;
}
