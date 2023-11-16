#include <QApplication>
#include "mazewidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    const int numRows = 5;
    const int numCols = 5;

    Matrix myMatrix(numRows, numCols);

    // зполнение матрицы по вертикали и горизонтали
    myMatrix.setVerticalValue(numRows, numCols);
    myMatrix.setHorizontalValue(numRows, numCols);

    // создание виджета и установка матрицы
    MazeWidget mazeWidget;
    mazeWidget.setMatrix(myMatrix);

    // отображение виджета
    mazeWidget.show();

    return a.exec();
}
