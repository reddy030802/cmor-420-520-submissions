// homework-2/include/matrix.h
#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int m;
    int n;
    double **data;
} Matrix;

// functions
Matrix init_matrix_contiguous(int m, int n);
Matrix init_matrix_non_contiguous(int m, int n);
void free_matrix_contiguous(Matrix *matrix);
void free_matrix_non_contiguous(Matrix *matrix);
void matvec(double * b, const Matrix * A, const double * x);
void matvec_transpose(double * b, const Matrix * A, const double * x);

#endif // MATRIX_H
