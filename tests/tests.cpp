#include <gtest/gtest.h>
#include <filesystem>

#include "../Maze/matrix.h"
#include "../Maze/mazeSolver.h"

TEST(MatrixTest, GenerateMaze) {
  Matrix matrix(5, 5);

  matrix.generateMaze();
  EXPECT_EQ(matrix.getRows(), 5);
  EXPECT_EQ(matrix.getColumns(), 5);

  for (int i = 0; i < matrix.getRows(); ++i) {
    for (int j = 0; j < matrix.getColumns(); ++j) {
      EXPECT_TRUE(matrix.getVerticalValue(i, j) == 0 ||
                  matrix.getVerticalValue(i, j) == 1);
      EXPECT_TRUE(matrix.getHorizontalValue(i, j) == 0 ||
                  matrix.getHorizontalValue(i, j) == 1);
    }
  }
}

TEST(MatrixTest, GenerateMaze1) {
  Matrix matrix(3, 3);
  matrix.generateMaze();

  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getColumns(), 3);

  for (int i = 0; i < matrix.getRows(); ++i) {
    for (int j = 0; j < matrix.getColumns(); ++j) {
      if (!(i == 2 && j == 1) && !(i == 2 && j == 2)) {
        EXPECT_TRUE(matrix.getVerticalValue(i, j) == 0 ||
                    matrix.getVerticalValue(i, j) == 1);
        EXPECT_TRUE(matrix.getHorizontalValue(i, j) == 0 ||
                    matrix.getHorizontalValue(i, j) == 1);
      }
    }
  }
}

TEST(MatrixTest, GenerateMaze3) {
  Matrix matrix(2, 2);
  matrix.generateMaze();

  EXPECT_EQ(matrix.getRows(), 2);
  EXPECT_EQ(matrix.getColumns(), 2);

  for (int i = 0; i < matrix.getRows(); ++i) {
    for (int j = 0; j < matrix.getColumns(); ++j) {
      EXPECT_TRUE(matrix.getVerticalValue(i, j) == 0 ||
                  matrix.getVerticalValue(i, j) == 1);
      EXPECT_TRUE(matrix.getHorizontalValue(i, j) == 0 ||
                  matrix.getHorizontalValue(i, j) == 1);
    }
  }
}

TEST(MatrixTest, GenerateMaze4) {
  Matrix matrix(4, 6);
  matrix.generateMaze();

  EXPECT_EQ(matrix.getRows(), 4);
  EXPECT_EQ(matrix.getColumns(), 6);

  for (int i = 0; i < matrix.getRows(); ++i) {
    for (int j = 0; j < matrix.getColumns(); ++j) {
      EXPECT_TRUE(matrix.getVerticalValue(i, j) == 0 ||
                  matrix.getVerticalValue(i, j) == 1);
      EXPECT_TRUE(matrix.getHorizontalValue(i, j) == 0 ||
                  matrix.getHorizontalValue(i, j) == 1);
    }
  }
}

TEST(MatrixTest, GenerateMaze5) {
  Matrix matrix(1, 1);
  matrix.generateMaze();

  EXPECT_EQ(matrix.getRows(), 1);
  EXPECT_EQ(matrix.getColumns(), 1);

  EXPECT_TRUE(matrix.getVerticalValue(0, 0) == 0 ||
              matrix.getVerticalValue(0, 0) == 1);
  EXPECT_TRUE(matrix.getHorizontalValue(0, 0) == 0 ||
              matrix.getHorizontalValue(0, 0) == 1);
}

TEST(MatrixTest, GenerateMaze6) {
  Matrix matrix(3, 3);
  matrix.generateMaze();

  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getColumns(), 3);

  for (int i = 0; i < matrix.getRows(); ++i) {
    for (int j = 0; j < matrix.getColumns(); ++j) {
      if (!(i == 2 && j == 1) && !(i == 2 && j == 2)) {
        EXPECT_TRUE(matrix.getVerticalValue(i, j) == 0 ||
                    matrix.getVerticalValue(i, j) == 1);
        EXPECT_TRUE(matrix.getHorizontalValue(i, j) == 0 ||
                    matrix.getHorizontalValue(i, j) == 1);
      }
    }
  }
}

TEST(MatrixTest, GenerateMaze9) {
  Matrix matrix(3, 5);
  matrix.generateMaze();

  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getColumns(), 5);

  for (int i = 0; i < matrix.getRows(); ++i) {
    for (int j = 0; j < matrix.getColumns(); ++j) {
      EXPECT_TRUE(matrix.getVerticalValue(i, j) == 0 ||
                  matrix.getVerticalValue(i, j) == 1);
      EXPECT_TRUE(matrix.getHorizontalValue(i, j) == 0 ||
                  matrix.getHorizontalValue(i, j) == 1);
    }
  }
}

TEST(MatrixTest, MazeIncorrectSize) {
  EXPECT_THROW(
      {
        try {
          Matrix matrix(60, 70);
        } catch (const std::invalid_argument& e) {
          EXPECT_STREQ(e.what(),
                       "Matrix size exceeds the maximum limit of 50x50");
          throw;
        }
      },
      std::invalid_argument);
}

TEST(MatrixTest, GenerateMaze2) {
  int numRows = 10;
  int numCols = 10;
  Matrix matrix(numRows, numCols);
  matrix.generateMaze();

  bool is_right = false;
  bool is_bottom = false;

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      if (matrix.getVerticalValue(i, j) == 1 ||
          matrix.getVerticalValue(i, j) == 0) {
        is_bottom = true;
      }
      if (matrix.getHorizontalValue(i, j) == 1 ||
          matrix.getHorizontalValue(i, j) == 0) {
        is_right = true;
      }
    }
  }

  ASSERT_TRUE(is_bottom);
  ASSERT_TRUE(is_right);
  std::string path = "examples/generatedInTest.txt";
  matrix.saveMaze(path);
}

TEST(MatrixTest, LoadMazeSuccess) {
  Matrix matrix;
  ASSERT_NO_THROW(matrix.loadMaze("examples/4x4.txt", std::filesystem::current_path()));

  ASSERT_EQ(matrix.getRows(), 4);
  ASSERT_EQ(matrix.getColumns(), 4);
  ASSERT_EQ(matrix.getVerticalValue(0, 0), 0);
  ASSERT_EQ(matrix.getHorizontalValue(0, 0), 1);
}

TEST(MatrixTest, LoadMazeInvalidFormat) {
  Matrix matrix;
  ASSERT_THROW(matrix.loadMaze("examples/invalid_format_maze.txt", std::filesystem::current_path()),
               std::runtime_error);
  ASSERT_EQ(matrix.getRows(), 0);
  ASSERT_EQ(matrix.getColumns(), 0);
}

TEST(MatrixTest, LoadMazeInvalidData) {
  Matrix matrix;
  ASSERT_THROW(matrix.loadMaze("examples/invalid_data_maze.txt", std::filesystem::current_path()),
               std::runtime_error);
  ASSERT_EQ(matrix.getRows(), 0);
  ASSERT_EQ(matrix.getColumns(), 0);
}

TEST(MazeSolverTest, ValidPathFound) {
  MazeSolver mazeSolver;
  std::pair<int, int> src = {0, 0};
  std::pair<int, int> dest = {9, 9};
  mazeSolver.parseMaze("examples/10x10v1.txt");
  std::vector<std::vector<int>> result = mazeSolver.findPath(src, dest);
  EXPECT_EQ(48, result[dest.first][dest.second]);
}

TEST(MazeSolverTest, SameCoordinates) {
  MazeSolver mazeSolver;
  std::pair<int, int> src = {4, 4};
  std::pair<int, int> dest = {4, 4};
  mazeSolver.parseMaze("../examples/10x10v1.txt");
  ASSERT_THROW(mazeSolver.findPath(src, dest), std::string);
}

TEST(MazeSolverTest, CoordinatesOutOfRange) {
  MazeSolver mazeSolver;
  std::pair<int, int> src = {-4, 4};
  std::pair<int, int> dest = {4, -4};
  mazeSolver.parseMaze("../examples/10x10v1.txt");
  ASSERT_THROW(mazeSolver.findPath(src, dest), std::string);
}

TEST(MazeSolverTest, InvalidCoordinates) {
  MazeSolver mazeSolver;
  std::pair<int, int> src = {222, 4};
  std::pair<int, int> dest = {4, 222};
  mazeSolver.parseMaze("../examples/10x10v1.txt");
  ASSERT_THROW(mazeSolver.findPath(src, dest), std::string);
}

TEST(MazeSolverTest, PathNotFound) {
  MazeSolver mazeSolver;
  std::pair<int, int> src = {0, 0};
  std::pair<int, int> dest = {3, 3};
  mazeSolver.parseMaze("../examples/10x10v2.txt");
  ASSERT_THROW(mazeSolver.findPath(src, dest), std::string);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
