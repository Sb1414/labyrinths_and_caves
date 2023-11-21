#include "mazewidget.h"
#include <QPainter>

MazeWidget::MazeWidget(QWidget *parent) : QWidget(parent), mazeMatrix(10, 10) {
    setFixedSize(500, 500);
}

void MazeWidget::setMatrix(const Matrix &matrix) {
    mazeMatrix = matrix;
    update(); // вызывает paintEvent для перерисовки виджета
}

void MazeWidget::setSolution(const QVector<QPoint>& solution) {
    solutionPath = solution;
    update(); // Вызывает paintEvent для перерисовки виджета с учетом решения
}

void MazeWidget::clearSolution() {
    solutionPath.clear();
    update(); // вызываем update, чтобы перерисовать виджет без пути
}

void MazeWidget::drawMaze(QPainter& painter) {
    int cellWidth = width() / mazeMatrix.getColumns();
    int cellHeight = height() / mazeMatrix.getRows();

    // отрисовка лабиринта
    for (int row = 0; row < mazeMatrix.getRows(); row++) {
        for (int col = 0; col < mazeMatrix.getColumns() - 1; col++) {
            if (mazeMatrix.getVerticalValue(row, col) == 1) {
                painter.fillRect((col + 1) * cellWidth, row * cellHeight, 1, cellHeight, Qt::green);
            }
        }
    }

    for (int row = 0; row < mazeMatrix.getRows() - 1; row++) {
        for (int col = 0; col < mazeMatrix.getColumns(); col++) {
            if (mazeMatrix.getHorizontalValue(row, col) == 1) {
                painter.fillRect(col * cellWidth, (row + 1) * cellHeight, cellWidth, 1, Qt::green);
            }
        }
    }
}

void MazeWidget::drawSolution(QPainter& painter) {
    int pathSize = solutionPath.size();
    int cellWidth = width() / mazeMatrix.getColumns();
    int cellHeight = height() / mazeMatrix.getRows();

    for (int i = 0; i < pathSize - 1; i++) {
        QPoint currentPoint = solutionPath[i];
        QPoint nextPoint = solutionPath[i + 1];

        int startX = currentPoint.x() * cellWidth + cellWidth / 2;
        int startY = currentPoint.y() * cellHeight + cellHeight / 2;

        int endX = nextPoint.x() * cellWidth + cellWidth / 2;
        int endY = nextPoint.y() * cellHeight + cellHeight / 2;

        painter.drawLine(startX, startY, endX, endY);
    }
}

void MazeWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);

    // Отрисовка лабиринта
    drawMaze(painter);

    // Отрисовка решения
    drawSolution(painter);
}


