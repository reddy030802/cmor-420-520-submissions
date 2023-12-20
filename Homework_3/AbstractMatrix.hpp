#ifndef ABSTRACTMATRIX_HPP
#define ABSTRACTMATRIX_HPP

class AbstractMatrix {
public:
    virtual ~AbstractMatrix() {}

    virtual double& operator()(int row, int column) = 0;
    virtual double operator()(int row, int column) const = 0;
    virtual int num_rows() const = 0;
    virtual int num_cols() const = 0;

};

#endif // ABSTRACTMATRIX_HPP

