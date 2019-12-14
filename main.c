#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


int main() {

    struct SquareMatrix m = initMatrix(3);

    for (int i = 0; i != m.size; ++i) {
        for (int j = 0; j != m.size; ++j) {
            m.matrix[i][j] = i + j;
        }
    }

    printMatrix(m);
    freeMatrix(m);

    return 0;
}
