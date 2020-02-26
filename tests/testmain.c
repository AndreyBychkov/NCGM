//
// Created by а on 15.12.2019.
//
#include <stdio.h>
#include "vector_tests.h"
#include "matrix_tests.h"
#include "optimizations_tests.h"
#include "vector_benchmarks.h"
#include "matrix_benchmarks.h"
#include "optimization_benchmarks.h"

int main(void) {

    vectorTestSuite();
    matrixTestSuite();
    optimizationTestSuite();
    vectorBenchmarkSuite();
    matrixBenchmarkSuite();
    optimizationBenchmarkSuite();

    return 0;
}

