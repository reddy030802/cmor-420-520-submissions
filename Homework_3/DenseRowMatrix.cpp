#include "DenseRowMatrix.hpp"
#include <cstring>
#include <stdexcept>

DenseRowMatrix::DenseRowMatrix(int rows, int cols) : _rows(rows), _cols(cols) {
    _data = new double[rows * cols];
    std::memset(_data, 0, sizeof(double) * rows * cols); // Initialize with zeros
}

DenseRowMatrix::~DenseRowMatrix() {
    delete[] _data;
}

double& DenseRowMatrix::operator()(int row, int column) {
    if (row >= _rows || column >= _cols || row < 0 || column < 0) {
        throw std::out_of_range("Matrix index out of bounds");
    }
    return _data[row * _cols + column];
}

double DenseRowMatrix::operator()(int row, int column) const {
    if (row >= _rows || column >= _cols || row < 0 || column < 0) {
        throw std::out_of_range("Matrix index out of bounds");
    }
    return _data[row * _cols + column];
}

int DenseRowMatrix::num_rows() const {
    return _rows;
}

int DenseRowMatrix::num_cols() const {
    return _cols;
}
