#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

class MazeSolver {
private:
  std::vector<std::vector<int>> vertical;
  std::vector<std::vector<int>> horizontal;
  int rows;
  int cols;

  void coordinateValidation(std::pair<int, int> src, std::pair<int, int> dest);
  void makeWave(std::vector<std::vector<int>> &wave, std::pair<int, int> src,
                std::pair<int, int> dest);
  std::vector<std::vector<int>> makePath(std::vector<std::vector<int>> &wave,
                                         std::pair<int, int> dest);

public:
  MazeSolver();
  void parseMaze(std::string file_name);
  void renderM(std::vector<std::vector<int>> m);
  std::vector<std::vector<int>> findPath(std::pair<int, int> src,
                                         std::pair<int, int> dest);
};

#endif // MAZESOLVER_H
