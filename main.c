#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


int main() {
    struct SquareMatrix m = readFromStdIn();
    printMatrix(m);
    freeMatrix(m);

    return 0;
}
