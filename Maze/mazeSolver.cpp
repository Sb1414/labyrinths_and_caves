// MazeSolver.cpp
#include "mazeSolver.h"

MazeSolver::MazeSolver() : rows(0), cols(0) {}

void MazeSolver::renderM(std::vector<std::vector<int>> m) {
    std::cout <<  rows << ' ' << cols << std::endl;
    for (size_t i = 0; i < m.size(); i++) {
        for (size_t j = 0; j < m[i].size(); j++) {
            std::cout << std::setw(3) << m[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void MazeSolver::parseMaze(std::string file_name) {
    std::ifstream data_maze(file_name);
    if (data_maze.is_open()) {
        data_maze >> rows >> cols;
        if (rows < 0 || cols < 0 || rows > 50 || cols > 50) {
            throw std::string{"Incorrect size"};
        }
        vertical.resize(rows, std::vector<int>(cols, -1));
        horizontal.resize(rows, std::vector<int>(cols, -1));
        for (auto i = 0; i < rows; i++) {
            for (auto j = 0; j < cols; j++) {
                data_maze >> vertical[i][j];
            }
        }
        for (auto i = 0; i < rows; i++) {
            for (auto j = 0; j < cols; j++) {
                data_maze >> horizontal[i][j];
            }
        }
    }
    data_maze.close();
    // renderM(vertical);
    // renderM(horizontal);
}

void MazeSolver::coordinateValidation(std::pair<int, int> src, std::pair<int, int> dest) {
    if (src == dest) {
        throw std::string{"Incorrect coordinates: start and finish coordinates are same"};
    }
    if (src.first < 0 || src.first >= rows || src.second < 0 || src.second >= rows ||
        dest.first < 0 || dest.first >= cols || dest.second < 0 || dest.second >= rows) {
        throw std::string{"Incorrect coordinates: out of range"};
    }
}

void MazeSolver::makeWave(std::vector<std::vector<int>> &wave, std::pair<int, int> src, std::pair<int, int> dest) {
    std::queue<std::pair<int, int>> q;
    wave[src.first][src.second] = 0;
    q.push(src);
    while (!q.empty()) {
        int row = q.front().first;
        int col = q.front().second;
        if (row-1 > -1 && wave[row-1][col] == -1 && !horizontal[row-1][col]) {
            wave[row-1][col] = wave[row][col] + 1;
            if (row-1 == dest.first && col == dest.second) break;
            q.push({row-1, col});
        }
        if (row+1 < rows && wave[row+1][col] == -1 && !horizontal[row][col]) {
            wave[row+1][col] = wave[row][col] + 1;
            if (row+1 == dest.first && col == dest.second) break;
            q.push({row+1, col});
        }
        if (col-1 > -1 && wave[row][col-1] == -1 && !vertical[row][col-1]) {
            wave[row][col-1] = wave[row][col] + 1;
            if (row == dest.first && col-1 == dest.second) break;
            q.push({row, col-1});
        }
        if (col+1 < cols && wave[row][col+1] == -1 && !vertical[row][col]) {
            wave[row][col+1] = wave[row][col] + 1;
            if (row == dest.first && col+1 == dest.second) break;
            q.push({row, col+1});
        }
        q.pop();
    }
    if (wave[dest.first][dest.second] == -1) 
        throw std::string{"Path not found"};
}

std::vector<std::vector<int>> MazeSolver::makePath(std::vector<std::vector<int>> &wave, std::pair<int, int> src, std::pair<int, int> dest) {
    std::vector<std::vector<int>> path(rows, std::vector<int>(cols, -1));
    auto cell = dest;
    for (int n = wave[dest.first][dest.second] - 1; n >= 0; n--) {
        path[cell.first][cell.second] = wave[cell.first][cell.second];
        if (cell.first-1 > -1 && wave[cell.first-1][cell.second] == n
            && !horizontal[cell.first-1][cell.second]) {
            cell.first--;
        }
        if (cell.first+1 < rows && wave[cell.first+1][cell.second] == n
            && !horizontal[cell.first][cell.second]) {
            cell.first++;
        }
        if (cell.second-1 > -1 && wave[cell.first][cell.second-1] == n
            && !vertical[cell.first][cell.second-1]) {
            cell.second--;
        }
        if (cell.second+1 < cols && wave[cell.first][cell.second+1] == n
            && !vertical[cell.first][cell.second]) {
            cell.second++;
        }
    }
    path[cell.first][cell.second] = wave[cell.first][cell.second];
    return path;
}

std::vector<std::vector<int>> MazeSolver::findPath(std::pair<int, int> src, std::pair<int, int> dest) {
    coordinateValidation(src, dest);
    std::cout << "coordinateValidation";
    std::vector<std::vector<int>> wave(rows, std::vector<int>(cols, -1));
    std::cout << "wave";
    makeWave(wave, src, dest);
    std::cout << "makeWave";
    renderM(wave);
    std::cout << "renderM";
    return makePath(wave, src, dest);
}
