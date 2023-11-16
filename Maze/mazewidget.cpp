#include "mazewidget.h"
#include <QPainter>

MazeWidget::MazeWidget(QWidget *parent) : QWidget(parent), mazeMatrix(10, 10) {
    setFixedSize(300, 300);
}


void MazeWidget::setMatrix(const Matrix &matrix) {
    mazeMatrix = matrix;
    update(); // вызывает paintEvent для перерисовки виджета
}

void MazeWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);

    int cellWidth = width() / mazeMatrix.getColumns();
    int cellHeight = height() / mazeMatrix.getRows();

    for (int row = 0; row < mazeMatrix.getRows(); row++) {
        for (int col = 0; col < mazeMatrix.getColumns() - 1; col++) {
            if (mazeMatrix.getVerticalValue(row, col) == 1) {
                painter.fillRect((col + 1) * cellWidth, row * cellHeight, 1, cellHeight, Qt::black);
            }
        }
    }

    for (int row = 0; row < mazeMatrix.getRows() - 1; row++) {
        for (int col = 0; col < mazeMatrix.getColumns(); col++) {
            if (mazeMatrix.getHorizontalValue(row, col) == 1) {
                painter.fillRect(col * cellWidth, (row + 1) * cellHeight, cellWidth, 1, Qt::black);
            }
        }
    }
}
