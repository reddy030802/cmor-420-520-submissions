#include "SparseMatrixCSR.hpp"
#include <stdexcept>

SparseMatrixCSR::SparseMatrixCSR(int rows, int cols, int nonzeros, 
                                 int* row_indices, int* col_indices, double* values)
    : _rows(rows), _cols(cols), _nzval(new double[nonzeros]),
      _col_index(new int[nonzeros]), _row_index(new int[rows + 1]) {
    std::copy(values, values + nonzeros, _nzval);
    std::copy(col_indices, col_indices + nonzeros, _col_index);
    std::copy(row_indices, row_indices + rows + 1, _row_index);
}

SparseMatrixCSR::~SparseMatrixCSR() {
    delete[] _nzval;
    delete[] _col_index;
    delete[] _row_index;
}

double SparseMatrixCSR::operator()(int row, int column) const {
    if (row >= _rows || row < 0) {
        throw std::out_of_range("Row index out of bounds");
    }
    for (int i = _row_index[row]; i < _row_index[row + 1]; ++i) {
        if (_col_index[i] == column) {
            return _nzval[i];
        }
    }
    return 0.0; 
}

int SparseMatrixCSR::num_rows() const {
    return _rows;
}

int SparseMatrixCSR::num_cols() const {
    return _cols;
}
