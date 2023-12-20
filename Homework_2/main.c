#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int m = 3;
    int n = 3;

    // initialize matrices
    Matrix A_cont = init_matrix_contiguous(m, n);
    Matrix A_non_cont = init_matrix_non_contiguous(m, n);

    // matrix-vector multiplication
    double x[] = {1, 2, 3};
    double b[m];  // Result vector

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            A_cont.data[i][j] = i + j;  
            A_non_cont.data[i][j] = i - j;  
        }
    }

    // matrix-vector multiplication
    matvec(b, &A_cont, x);

    printf("Result of matrix-vector multiplication (contiguous storage):\n");
    for (int i = 0; i < m; i++) {
        printf("%f ", b[i]);
    }
    printf("\n");

    // non-contiguous matrix
    matvec(b, &A_non_cont, x);

    printf("Result of matrix-vector multiplication (non-contiguous storage):\n");
    for (int i = 0; i < m; i++) {
        printf("%f ", b[i]);
    }
    printf("\n");

    // allocated matrices
    free_matrix_contiguous(&A_cont);
    free_matrix_non_contiguous(&A_non_cont);

    return 0;
}
