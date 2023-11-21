// MazeController.cpp
#include "MazeController.h"

MazeController::MazeController(int numRows, int numCols) : myMatrix(numRows, numCols) {}

void MazeController::generateMaze() {
    myMatrix.generateMaze();
}

void MazeController::solveMaze(std::pair<int, int> src, std::pair<int, int> dest) {
    std::ifstream file("awd.txt");
    if (!file.is_open()) {
        std::cerr << "Error: File 'awd.txt' not found.\n";
        return;
    }

    mazeSolver.parseMaze("awd.txt");
    std::vector<std::vector<int>> wave = mazeSolver.findPath(src, dest);
}

void MazeController::saveMatrixToFile(const std::string& fileName) {
    myMatrix.saveMaze(fileName);
}

const Matrix& MazeController::getMatrix() const {
    return myMatrix;
}
