#include <QApplication>
#include <iostream>

#include "mainwindow.h"
#include "mazeSolver.h"
#include "mazewidget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
