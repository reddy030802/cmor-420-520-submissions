#ifndef SPARSEMATRIXCSR_HPP
#define SPARSEMATRIXCSR_HPP

#include "AbstractMatrix.hpp"

class SparseMatrixCSR : public AbstractMatrix {
private:
    double* _nzval;
    int* _col_index;
    int* _row_index;
    int _rows, _cols;

public:
    SparseMatrixCSR(int rows, int cols, int nonzeros, 
                    int* row_indices, int* col_indices, double* values);
    virtual ~SparseMatrixCSR();

    double operator()(int row, int column) const override;
    int num_rows() const override;
    int num_cols() const override;

};

#endif // SPARSEMATRIXCSR_HPP


