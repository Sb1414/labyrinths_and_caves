#include "matrix.h"
#include <cstdlib> // for rand function
#include <cstdlib>   // Подключаем библиотеку для работы с функциями, связанными с генерацией случайных чисел
#include <ctime>
#include <algorithm>
#include <random>

Matrix::Matrix(int numRows, int numCols) : rows(numRows), cols(numCols) {
    vertical.resize(rows + 1, std::vector<int>(cols, 0));
    horizontal.resize(rows, std::vector<int>(cols + 1, 0));

    sets.resize(rows, std::vector<int>(cols, -1));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sets[i][j] = j +1;
            horizontal[i][j] = 1;
            std::cout << sets[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int Matrix::getRows() const {
    return rows;
}

int Matrix::getColumns() const {
    return cols;
}

int Matrix::getVerticalValue(int row, int col) const {
    return vertical[row][col];
}

int Matrix::getHorizontalValue(int row, int col) const {
    return horizontal[row][col];
}

int Matrix::getSetValue(int row, int col) const {
    return sets[row][col];
}


std::vector<int> generateVector(int size) {
    // Создаем вектор, заполненный единицами
    std::vector<int> result(size, 1);

    // Добавляем один ноль в рандомную позицию
    result[rand() % size] = 0;

    return result;
}

void Matrix::generateMaze() {
    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            vertical[i][j] = rand() & 1;

            if (j != 0 && vertical[i][j-1] == 0)
            {
                sets[i][j] = sets[i][j-1]; // предыдущему переприсваиваю номер множества, если стенки нет
            }

            if (i == rows - 1) // для ласт ряда
            {
                sets[i][j] = sets[i-1][j];

                if (sets[i][j-1] == sets[i][j] && j > 0) {
                    vertical[i][j] = rand() & 1;
                } else if (sets[i][j-1] != sets[i][j] && j > 0) {
                    sets[i][j] = sets[i][j-1];
                    vertical[i][j] = 0;
                }

            }

            std::cout << sets[i][j] << " ";
        }

        for (int j = 0; j < cols; )
        {
            int size_this_set = 0, itterator = 0;

            while (sets[i][size_this_set+1+j] == sets[i][size_this_set+j]) {
                size_this_set++;
            }

            if (size_this_set != 0) {
                std::vector<int> values = generateVector(size_this_set+1);
                std::cout << " vector: ";
                for (int v : values) {
                    std::cout << "[" << i << "][" << j << "] - " << v  << ", ";
                    horizontal[i][itterator+j] = v;
                    j++;
                }
                std::cout << "; " << j << " <- j ";
            } else if (sets[i][j+1] != sets[i][j] && j != cols-1) {
                std::cout << " мне похуй снова j = " << j << "; ";
                horizontal[i][j] = 0;
                j++;
            } else if (sets[i][j-1] != sets[i][j] && j == cols-1) {
                std::cout << " мне похуй j = " << j << "; ";
                horizontal[i][j] = 0;
                j++;
            } else {
                std::cout << " тут else j = " << j << "; ";
                horizontal[i][j] = 1;
                j++;
            }
        }

        std::cout << "\n";
//        if (i != rows -1)
//            checkHorizontalInRow(i);
    }
}

void Matrix::checkSetInRow(int i) {
    int firstSetValue = sets[i][0];
    bool allSame = true;

    for (int j = 1; j < cols; j++) {
        if (sets[i][j] != firstSetValue) {
            allSame = false;
            break;
        }
    }

    if (allSame) {
        for (int j = 0; j < cols; j++)
        {
            vertical[i][j] = rand() & 1;

            if (j != 0 && vertical[i][j-1] == 0)
            {
                sets[i][j] = sets[i][j-1]; // предыдущему переприсваиваю номер множества, если стенки нет

            }
        }
    }
}

void Matrix::checkHorizontalInRow(int i) {
    std::vector<int> uniqueSets;
    for (int j = 0; j < cols; j++) {
        if (std::find(uniqueSets.begin(), uniqueSets.end(), sets[i][j]) == uniqueSets.end()) {
            uniqueSets.push_back(sets[i][j]);
        }
    }

    // перебор по уникальным номерам сета
    for (int setNumber : uniqueSets) {
        // индексы ячеек с текущим номером сета
        std::vector<int> cellsWithSet;
        for (int j = 0; j < cols; j++) {
            if (sets[i][j] == setNumber) {
                cellsWithSet.push_back(j);
            }
        }

        // если только одна ячейка с определенным номером (стенки вокруг), удаляем нижнюю стенку
        if (cellsWithSet.size() == 1) {
            int singleCell = cellsWithSet[0];
            horizontal[i][singleCell] = 0;
        }
        // когда несколько ячеек с одинаковым номером, удаляем рандомно нижнюю стенку
        else if (cellsWithSet.size() > 1) {
            int randomIndex = rand() % cellsWithSet.size();
            int randomCell = cellsWithSet[randomIndex];

            horizontal[i][randomCell] = 0;
        }
    }
}
