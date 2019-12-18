cmake_minimum_required(VERSION 3.12)
project(Test C)

set(CMAKE_C_STANDARD 11)

add_executable(Main main.c matrix.c optimization.c optimization.h vector.c vector.h)
add_executable(Tests tests/testmain.c
        tests/vector_tests.c vector.c
        tests/matrix_tests.c tests/matrix_tests.h matrix.c
        tests/optimizations_tests.c tests/optimizations_tests.h optimization.h optimization.c)