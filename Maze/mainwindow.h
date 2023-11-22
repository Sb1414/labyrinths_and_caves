#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mazewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_btnGenerateMaze_clicked();
  void on_btnSolveMaze_clicked();
  void on_spinBoxRows_valueChanged(int arg1);
  void on_spinBoxCols_valueChanged(int arg1);

  void on_btnLoadMazeFromFile_clicked();

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
