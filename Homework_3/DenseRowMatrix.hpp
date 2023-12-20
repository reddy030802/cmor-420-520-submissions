#ifndef DENSEROWMATRIX_HPP
#define DENSEROWMATRIX_HPP

#include "AbstractMatrix.hpp"

class DenseRowMatrix : public AbstractMatrix {
private:
    double* _data;
    int _rows, _cols;

public:
    DenseRowMatrix(int rows, int cols);
    virtual ~DenseRowMatrix();

    double& operator()(int row, int column) override;
    double operator()(int row, int column) const override;
    int num_rows() const override;
    int num_cols() const override;

};

#endif // DENSEROWMATRIX_HPP


