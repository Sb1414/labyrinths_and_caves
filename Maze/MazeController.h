// MazeController.h
#ifndef MAZECONTROLLER_H
#define MAZECONTROLLER_H

#include "matrix.h"
#include "mazeSolver.h"

class MazeController {
public:
    MazeController(int numRows, int numCols);

    void generateMaze();
    void solveMaze(std::pair<int, int> src, std::pair<int, int> dest);
    void saveMatrixToFile(const std::string& fileName);
    void loadMatrixFromFile(const std::string& fileName);
    const Matrix& getMatrix() const;

private:
    Matrix myMatrix;
    MazeSolver mazeSolver;
};

#endif // MAZECONTROLLER_H
