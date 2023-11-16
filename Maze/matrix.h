#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

class Matrix {
private:
    int rows;
    int cols;
    std::vector<std::vector<int>> vertical;
    std::vector<std::vector<int>> horizontal;

public:
    Matrix(int numRows, int numCols);
    int getRows() const;
    int getColumns() const;
    void setVerticalValue(int row, int col);
    int getVerticalValue(int row, int col) const;
    void setHorizontalValue(int row, int col);
    int getHorizontalValue(int row, int col) const;
};

#endif // MATRIX_H
