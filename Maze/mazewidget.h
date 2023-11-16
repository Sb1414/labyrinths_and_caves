#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H

#include <QWidget>
#include "matrix.h"

class MazeWidget : public QWidget {
    Q_OBJECT

private:
    Matrix mazeMatrix;

public:
    MazeWidget(QWidget *parent = nullptr);
    void setMatrix(const Matrix &matrix);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MAZEWIDGET_H
