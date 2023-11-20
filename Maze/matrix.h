#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <fstream>

class Matrix {
private:
    int rows;
    int cols;
    std::vector<std::vector<int>> vertical;
    std::vector<std::vector<int>> horizontal;
    std::vector<std::vector<int>> sets;

public:
    Matrix(int numRows, int numCols);
    int getRows() const;
    int getColumns() const;
    int getVerticalValue(int row, int col) const;
    int getHorizontalValue(int row, int col) const;
    int getSetValue(int row, int col) const;
    void checkSetInRow(int i);
    void checkHorizontalInRow(int i);
    void generateMaze();
    void saveMaze(const std::string& fileName) const;
};

#endif // MATRIX_H
