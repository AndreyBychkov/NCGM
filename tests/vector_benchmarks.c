//
// Created by а on 26.02.2020.
//

#include "vector_benchmarks.h"
#include "../vector.h"
#include "../vector_omp.h"
#include "time.h"
#include "math.h"

void scalarCompositionOMPBenchmark() {
    size_t size = 1000;
    struct Vector first = randomVector(size);
    struct Vector second = randomVector(size);
    double resSequential;
    double resOMP;
    clock_t start, finish;

    printf("scalarCompositionOMPBenchmark:\n");
    start = clock();
    resSequential = scalarComposition(first, second);
    finish = clock();
    float seqTime = (float) (finish - start) / CLOCKS_PER_SEC;
    printf("Sequential time: %f\n", seqTime);

    start = clock();
    resOMP = scalarCompositionOMP(first, second);
    finish = clock();
    float parallelTime = (float) (finish - start) / CLOCKS_PER_SEC;
    printf("Parallel time: %f\n", parallelTime);

    printf("Time coefficient: %f\n", seqTime / parallelTime);
    if (fabs(resSequential - resOMP) > 1e-6) {
        printf("FAILED: Results are %0.3lf and %0.3lf not equal!\n", resSequential, resOMP);
    }

}

void vectorBenchmarkSuite() {
    for (size_t i = 0; i < 40; ++i) putchar('-');
    printf("\nVector benchmarks:\n\n");
    scalarCompositionOMPBenchmark();
}