#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
double time_matvec(void (*matvec_func)(double *, const Matrix *, const double *),
                   const Matrix *A, const double *x, int num_samples) {
    clock_t start, end;
    double cpu_time_used, total_time = 0.0;
    double *b = (double *)malloc(sizeof(double) * A->m);

    for (int i = 0; i < num_samples; ++i) {
        start = clock();
        matvec_func(b, A, x);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        total_time += cpu_time_used;
    }

    free(b);
    return total_time / num_samples;
}
int main(int argc, char *argv[]) {
    int m, n, num_samples;

    if (argc > 3) {
        m = atoi(argv[1]);
        n = atoi(argv[2]);
        num_samples = atoi(argv[3]);
    } else {
        m = n = 1000;
        num_samples = 10;
    }

    Matrix A_cont = init_matrix_contiguous(m, n);
    Matrix A_non_cont = init_matrix_non_contiguous(m, n);
    double *x = (double *)malloc(sizeof(double) * n);

    // contiguous and non-contiguous matrices
    double time_cont = time_matvec(matvec, &A_cont, x, num_samples);
    double time_non_cont = time_matvec(matvec, &A_non_cont, x, num_samples);
    double time_transpose_cont = time_matvec(matvec_transpose, &A_cont, x, num_samples);
    double time_transpose_non_cont = time_matvec(matvec_transpose, &A_non_cont, x, num_samples);

    // timing 
    printf("Average time for matvec (contiguous): %f seconds\n", time_cont);
    printf("Average time for matvec (non-contiguous): %f seconds\n", time_non_cont);
    printf("Average time for matvec_transpose (contiguous): %f seconds\n", time_transpose_cont);
    printf("Average time for matvec_transpose (non-contiguous): %f seconds\n", time_transpose_non_cont);

    free_matrix_contiguous(&A_cont);
    free_matrix_non_contiguous(&A_non_cont);
    free(x);

    return 0;
}
