#include <QApplication>
#include "mazeSolver.h"
#include "mazewidget.h"
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    const int numRows = 50;
    const int numCols = 50;

    Matrix myMatrix(numRows, numCols);
    MazeSolver mazeSolver;

    // зполнение матрицы по вертикали и горизонтали
    myMatrix.generateMaze();
    myMatrix.saveMaze("awd.txt");

    // создание виджета и установка матрицы
    MazeWidget mazeWidget;
    mazeWidget.setMatrix(myMatrix);

    // отображение виджета
    mazeWidget.show();

    // Решение лабиринта
    std::pair<int, int> src(0, 0);  // начальные координаты
    std::pair<int, int> dest(0, numCols - 1);  // конечные координаты
    mazeSolver.parseMaze("awd.txt");

    std::vector<std::vector<int>> wave = mazeSolver.findPath(src, dest);
    QVector<QPoint> path;
    for (size_t i = 0; i < wave.size(); ++i) {
        for (size_t j = 0; j < wave[i].size(); ++j) {
            if (wave[i][j] != -1) {
                path.append(QPoint(static_cast<int>(j), static_cast<int>(i)));
                std::cout << "[" << i << "][" << j << "] ";
            }
        }
    }

    auto compareFunction = [&](const QPoint& point1, const QPoint& point2) {
        return wave[point1.y()][point1.x()] < wave[point2.y()][point2.x()];
    };

    std::sort(path.begin(), path.end(), compareFunction);

    // установка решения в виджет
    mazeWidget.setSolution(path);

    return a.exec();
}

