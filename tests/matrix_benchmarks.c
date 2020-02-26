//
// Created by а on 26.02.2020.
//

#include "matrix_benchmarks.h"
#include "time.h"
#include "../matrix_omp.h"
#include "../vector_omp.h"

void dotProductOMPBenchmark() {
    size_t size = 10000;
    struct SquareMatrix m = randomMatrixOMP(size);
    struct Vector v = randomVector(size);
    struct Vector resSequential;
    struct Vector resParallel;
    clock_t start, finish;

    printf("dotProductOMPBenchmark:\n");

    start = clock();
    resSequential = dotProduct(m, v);
    finish = clock();
    float seq_time = (float) (finish - start) / CLOCKS_PER_SEC;
    printf("Sequential time: %f\n", seq_time);

    start = clock();
    resParallel = dotProductOMP(m, v);
    finish = clock();
    float parallel_time = (float) (finish - start) / CLOCKS_PER_SEC;
    printf("Parallel time: %f\n", parallel_time);

    printf("Time coefficient: %f\n", seq_time / parallel_time);

    bool isResEqual = equalsVector(resSequential, resParallel);
    if (!isResEqual) {
        printf("Results are not equal!");
    }

    freeMatrix(m);
    freeVector(v);
    freeVector(resSequential);
    freeVector(resParallel);
}

void matrixBenchmarkSuite() {
    for (size_t i = 0; i < 40; ++i) putchar('-');
    printf("\nMatrix benchmarks:\n\n");

    dotProductOMPBenchmark();
}
