//
// Created by а on 15.12.2019.
//
#include <stdio.h>
#include "vector_tests.h"
#include "matrix_tests.h"
#include "optimizations_tests.h"

int main(void) {

    vectorTestSuite();
    matrixTestSuite();
    optimizationTestSuite();

    return 0;
}

