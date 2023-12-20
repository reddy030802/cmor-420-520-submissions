#include "matrix.h"
#include <stdlib.h>

Matrix init_matrix_contiguous(int m, int n) {
    Matrix matrix;
    matrix.m = m;
    matrix.n = n;

    matrix.data = (double **) malloc(sizeof(double *) * m);
    if (matrix.data == NULL) {
    }
    matrix.data[0] = (double *) malloc(sizeof(double) * m * n);
    if (matrix.data[0] == NULL) {
    }

    for (int i = 1; i < m; ++i) {
        matrix.data[i] = matrix.data[0] + i * n;
    }

    return matrix;
}


Matrix init_matrix_non_contiguous(int m, int n) {
    Matrix matrix;
    matrix.m = m;
    matrix.n = n;

    matrix.data = (double **) malloc(sizeof(double *) * m);
    if (matrix.data == NULL) {
    }

    for (int i = 0; i < m; ++i) {
        matrix.data[i] = (double *) malloc(sizeof(double) * n);
        if (matrix.data[i] == NULL) {
        }
    }

    return matrix;
}

void free_matrix_contiguous(Matrix *matrix) {
    if (matrix && matrix->data) {
        free(matrix->data[0]); 
        free(matrix->data);   
    }
}


void free_matrix_non_contiguous(Matrix *matrix) {
    if (matrix && matrix->data) {
        for (int i = 0; i < matrix->m; ++i) {
            free(matrix->data[i]); 
        }
        free(matrix->data); 
    }
}

void matvec(double *b, const Matrix *A, const double *x) {
    for (int i = 0; i < A->m; i++) {
        b[i] = 0; 
        for (int j = 0; j < A->n; j++) {
            b[i] += A->data[i][j] * x[j]; 
        }
    }
}

void matvec_transpose(double *b, const Matrix *A, const double *x)
{
}
