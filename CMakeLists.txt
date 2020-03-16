cmake_minimum_required(VERSION 3.12)
project(NCGM C)

set(CMAKE_C_STANDARD 11)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(Main main.c
        matrix.h matrix.c
        optimization.c optimization.h
        vector.c vector.h
        matrix_omp.c matrix_omp.h
        optimization_omp.c optimization_omp.h
        vector_omp.c vector_omp.h matrix_mpi.c matrix_mpi.h)
add_executable(Tests tests/testmain.c
        tests/vector_tests.c vector.c
        tests/matrix_tests.c tests/matrix_tests.h matrix.c
        tests/optimizations_tests.c tests/optimizations_tests.h
        optimization.h optimization.c
        matrix_omp.c matrix_omp.h
        optimization_omp.c optimization_omp.h
        vector_omp.c vector_omp.h
        tests/vector_benchmarks.c tests/vector_benchmarks.h
        tests/optimization_benchmarks.c tests/optimization_benchmarks.h
        tests/matrix_benchmarks.c tests/matrix_benchmarks.h)


find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})
target_link_libraries(Main ${MPI_LIBRARIES})
target_link_libraries(Tests ${MPI_LIBRARIES})
message(${MPIEXEC_EXECUTABLE})


