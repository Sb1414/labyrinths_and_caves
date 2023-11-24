#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H

#include <QWidget>

#include "matrix.h"

class MazeWidget : public QWidget {
  Q_OBJECT

private:
  Matrix mazeMatrix;
  QVector<QPoint> solutionPath;

public slots:
  void setSolution(const QVector<QPoint> &solution);
  void drawMaze(QPainter &painter);
  void drawSolution(QPainter &painter);

public:
  explicit MazeWidget(QWidget *parent);
  //        MazeWidget(QWidget *parent = nullptr);
  void setMatrix(const Matrix &matrix);
  void loadMazeFromFile(const QString &filePath, const std::string &currentDir);
  void clearSolution();

protected:
  void paintEvent(QPaintEvent *event) override;
};

#endif // MAZEWIDGET_H
