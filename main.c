#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "vector.h"
#include "optimization.h"
#include "omp.h"

struct Vector minusGrad(struct Vector x, struct SquareMatrix hessian, struct Vector rightEqVector) {
    return multiplyVectorOnNumber(
            subtractVector(
                    dotProduct(hessian, x),
                    rightEqVector),
            -1);
}

void execute_ncgm() {
    int size = 0;
    scanf("%d", &size);
    struct SquareMatrix hessian = readMatrixFromStdInSized(size);

    struct Vector b = readVectorFromStdInSized(size);

    struct Vector xPredicted = optimizeFletcherReeves(hessian, b, minusGrad);
    printVector(xPredicted);

    freeMatrix(hessian);
    freeVector(b);
    freeVector(xPredicted);
}

int main() {
    int vsize = 100;
    struct Vector v1 = initVector(vsize);
    struct Vector v2 = initVector(vsize);
    struct Vector v3 = initVector(vsize);
    struct Vector v3_true = initVector(vsize);

    for (int i = 0; i < vsize; ++i) {
        v1.vector[i] = i;
        v2.vector[i] = i * i;
        v3_true.vector[i] = i + i*i;
    }

    #pragma omp parallel
    {

    #pragma omp for
        for (int i = 0; i < vsize; ++i) {
            v3.vector[i] = v1.vector[i] + v2.vector[i];
        }
    }

    printVector(v3);
    printf("%lf", meanAbsoluteErrorVector(v3, v3_true));

    freeVector(v1);
    freeVector(v2);
    freeVector(v3);
    freeVector(v3_true);
    return 0;
}
