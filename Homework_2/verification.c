#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 1-norm of the error
double compute_error(const double *b_exact, const double *b_computed, int length) {
    double error = 0.0;
    for (int i = 0; i < length; i++) {
        error += fabs(b_exact[i] - b_computed[i]);
    }
    return error;
}

int main() {
    int m = 2; 
    int n = 2; 

    Matrix A_cont = init_matrix_contiguous(m, n);
    Matrix A_non_cont = init_matrix_non_contiguous(m, n);
    double x[] = {1, 2}; 
    double b_cont[m], b_non_cont[m];
    double b_exact[] = {5, 11}; 

    A_cont.data[0][0] = 1; A_cont.data[0][1] = 2;
    A_cont.data[1][0] = 3; A_cont.data[1][1] = 4;

    A_non_cont.data[0][0] = 1; A_non_cont.data[0][1] = 2;
    A_non_cont.data[1][0] = 3; A_non_cont.data[1][1] = 4;

    // matrix-vector multiplication
    matvec(b_cont, &A_cont, x);
    matvec(b_non_cont, &A_non_cont, x);

    // error for contiguous matrix
    printf("The error in computing b=Ax for matvec with contiguous matrix storage is %e\n", 
           compute_error(b_exact, b_cont, m));

    // error for non-contiguous matrix
    printf("The error in computing b=Ax for matvec with non-contiguous matrix storage is %e\n", 
           compute_error(b_exact, b_non_cont, m));

    free_matrix_contiguous(&A_cont);
    free_matrix_non_contiguous(&A_non_cont);

    return 0;
}
