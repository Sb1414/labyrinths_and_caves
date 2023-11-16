#include "matrix.h"
#include <cstdlib> // for rand function

Matrix::Matrix(int numRows, int numCols) : rows(numRows), cols(numCols) {
    vertical.resize(rows + 1, std::vector<int>(cols, 0));
    horizontal.resize(rows, std::vector<int>(cols + 1, 0));
}

int Matrix::getRows() const {
    return rows;
}

int Matrix::getColumns() const {
    return cols;
}

void Matrix::setVerticalValue(int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            vertical[i][j] = rand() & 1;
            if (j == col - 1) {
                vertical[i][j] = 1;
            }
        }
    }
}

int Matrix::getVerticalValue(int row, int col) const {
    if (row >= 0 && row <= rows && col >= 0 && col < cols) {
        return vertical[row][col];
    } else {
        std::cout << "Некорректные индексы для вертикальной стенки" << std::endl;
        return 0; // можно вернуть какое-то значение по умолчанию
    }
}

void Matrix::setHorizontalValue(int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            horizontal[i][j] = rand() & 1;

            if (i == 0) {
                if (j == 0) {
                    vertical[i][j] == 1 ? horizontal[i][j] = 0 : horizontal[i][j] = rand() & 1;
                }
                if (j > 0 && vertical[i][j - 1] == 1 && vertical[i][j + 1] == 1) {
                    horizontal[i][j] = 0;
                } else {
                    horizontal[i][j] = rand() & 1;
                }
            }

            if (i == row - 1) {
                horizontal[i][j] = 1;
            }
        }
    }
}

int Matrix::getHorizontalValue(int row, int col) const {
    if (row >= 0 && row < rows && col >= 0 && col <= cols) {
        return horizontal[row][col];
    } else {
        std::cout << "Некорректные индексы для горизонтальной стенки" << std::endl;
        return 0; // можно вернуть какое-то значение по умолчанию
    }
}
