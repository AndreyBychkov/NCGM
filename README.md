# NCGM: Nonlinear conjugate gradient method.

[![Build Status](https://travis-ci.com/AndreyBychkov/NCGM.svg?branch=master)](https://travis-ci.com/AndreyBychkov/NCGM)

Package for solving systems of equations like **Hx = b**.

# API

### Initializing 

You can create matrices and vectors by `init` methods and special functions.

Example:
```c
struct Vector v = initVector(size);
struct Squarematrix m = initMatrix(size);

struct SquareMatix e = eyeMatrix(size);

struct Vector i = readVectorFromStdIn();
```

### Arithmetic operations

You can access operations like +, -, /, * by their name + data structure.

Example:
```c
struct Vector v = addVector(v1, v2);
struct Matrix m = nultiplyMatrixOnNumber(m2, 2);
```

Also, there are mutable versions of operations, which alters one of arguments.

Example:
```c
addMatrixMutable(chaging, term);
```

### Optimization

You can optimize your functions by Fletcher Reeves optimization procedure.

Example:
```c
struct Vector xPredicted = optimizeFletcherReeves(hessian, b, minusGrad);
```

### P.S.

Also you can use test for examples.