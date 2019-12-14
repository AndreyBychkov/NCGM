cmake_minimum_required(VERSION 3.15)
project(Test C)

set(CMAKE_C_STANDARD 11)

add_executable(Test main.c matrix.c optimization.c optimization.h vector.c vector.h)