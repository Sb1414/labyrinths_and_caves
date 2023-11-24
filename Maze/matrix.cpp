#include "matrix.h"

Matrix::Matrix(int numRows, int numCols) : rows(numRows), cols(numCols) {
  if (rows > 50 || cols > 50) {
    throw std::invalid_argument(
        "Matrix size exceeds the maximum limit of 50x50");
  }

  vertical.resize(rows + 1, std::vector<int>(cols, 0));
  horizontal.resize(rows, std::vector<int>(cols + 1, 0));

  sets.resize(rows, std::vector<int>(cols, -1));
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      sets[i][j] = j + 1;
    }
  }
}

int Matrix::getRows() const { return rows; }

int Matrix::getColumns() const { return cols; }

int Matrix::getVerticalValue(int row, int col) const {
  return vertical[row][col];
}

int Matrix::getHorizontalValue(int row, int col) const {
  return horizontal[row][col];
}

int Matrix::getSetValue(int row, int col) const { return sets[row][col]; }

std::vector<int> generateVector(int size) {
  std::vector<int> result(size, 1);
  result[rand() % size] = 0;
  return result;
}

void Matrix::generateMaze() {
  srand(static_cast<unsigned>(time(0)));

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      horizontal[i][j] = 1;
      vertical[i][j] = rand() & 1;

      if (j != 0 && vertical[i][j - 1] == 0) {
        sets[i][j] = sets[i][j - 1]; // предыдущему переприсваиваю номер
                                     // множества, если стенки нет
      }

      if (i == rows - 1) { // для ласт ряда
        sets[i][j] = sets[i - 1][j];
      }
    }

    if (i == rows - 1) { // для ласт ряда
      for (int j = 0; j < cols; j++) {
        if (sets[i][j + 1] == sets[i][j] && j < cols - 1 &&
            horizontal[i - 1][j] != 1 && horizontal[i - 1][j + 1] != 1 &&
            j < cols - 1) {
          vertical[i][j] = 1;
        } else if (sets[i][j + 1] != sets[i][j] && j < cols - 1) {
          sets[i][j] = sets[i][j - 1];
          vertical[i][j] = 0;
        } else {
          vertical[i][j] = 0;
        }
      }
    }

    for (int j = 0; j < cols;) { // добавляю нижнюю границу
      int size_this_set = 0, itterator = 0;

      while (sets[i][size_this_set + 1 + j] == sets[i][size_this_set + j]) {
        size_this_set++;
      }

      if (size_this_set != 0) {
        std::vector<int> values = generateVector(size_this_set + 1);
        for (int v : values) {
          horizontal[i][itterator + j] = v;
          j++;
        }
      } else if (sets[i][j + 1] != sets[i][j] && j != cols - 1) {
        horizontal[i][j] = 0;
        j++;
      } else if (sets[i][j - 1] != sets[i][j] && j == cols - 1) {
        horizontal[i][j] = 0;
        j++;
      } else {
        horizontal[i][j] = 1;
        j++;
      }
    }
  }
}

void Matrix::saveMaze(const std::string &fileName) const {
  std::filesystem::path outputPath(fileName);

  if (outputPath.is_relative()) {
    // если путь относительный, преобразуем его в абсолютный путь
    outputPath = std::filesystem::absolute(outputPath);
  }

  std::ofstream outputFile(outputPath);

  if (outputFile.is_open()) {
    outputFile << rows << ' ' << cols << '\n';

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        outputFile << vertical[i][j] << ' ';
      }
      outputFile << '\n';
    }

    outputFile << '\n';

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        outputFile << horizontal[i][j] << ' ';
      }
      outputFile << '\n';
    }

    outputFile.close();
    //        std::cout << "Maze saved to: " << outputPath << std::endl;
  } else {
    std::cerr << "Unable to open file for writing: " << outputPath << std::endl;
  }
}

void Matrix::loadMaze(const std::string &fileName,
                      const std::string &currentDir) {
  std::ifstream inputFile(fileName);

  if (inputFile.is_open()) {
    std::string rowsStr, colsStr;
    inputFile >> rowsStr >> colsStr;

    try {
      rows = std::stoi(rowsStr);
      cols = std::stoi(colsStr);
    } catch (const std::exception &e) {
      throw std::runtime_error("Invalid format: rows and cols must be numeric");
    }

    if (rows < 1 && cols < 1)
      throw std::runtime_error(
          "Invalid format: rows and columns cannot be less than 1");

    vertical.resize(rows + 1, std::vector<int>(cols, 0));
    horizontal.resize(rows, std::vector<int>(cols + 1, 0));
    sets.resize(rows, std::vector<int>(cols, -1));

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (!(inputFile >> vertical[i][j]) ||
            (vertical[i][j] != 0 && vertical[i][j] != 1)) {
          throw std::runtime_error("Invalid format: maze data must be 0 or 1");
        }
      }
    }

    std::string emptyLine;
    std::getline(inputFile, emptyLine);

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (!(inputFile >> horizontal[i][j]) ||
            (horizontal[i][j] != 0 && horizontal[i][j] != 1)) {
          throw std::runtime_error("Invalid format: maze data must be 0 or 1");
        }
      }
    }

    std::getline(inputFile, emptyLine);

    inputFile.close();

    saveMaze(currentDir + "/examples/awd.txt");
  } else {
    std::cerr << "Unable to open file for reading: " << fileName << std::endl;
  }
}
