#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include "mazeSolver.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->maze->clearSolution();
  ui->btnSolveMaze->setEnabled(false);

  ui->end_x->setMaximum(ui->spinBoxCols->value());
  ui->end_y->setMaximum(ui->spinBoxRows->value());
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_btnGenerateMaze_clicked() {
  try {
    const int numRows = ui->spinBoxRows->value();
    const int numCols = ui->spinBoxCols->value();

    ui->maze->clearSolution();

    Matrix myMatrix(numRows, numCols);
    MazeSolver mazeSolver;

    // зполнение матрицы по вертикали и горизонтали
    myMatrix.generateMaze();

    QString currentDir = QCoreApplication::applicationDirPath();

    std::string currentDirr = currentDir.toStdString();

    size_t foundPos = currentDirr.find("src/");
    std::string modifiedDir;

    if (foundPos != std::string::npos) {
      modifiedDir = currentDirr.substr(0, foundPos + 4);
    }

    myMatrix.saveMaze(modifiedDir + "/examples/awd.txt");

    // создание виджета и установка матрицы
    ui->maze->setMatrix(myMatrix);

    // отображение виджета
    ui->maze->show();
    ui->btnSolveMaze->setEnabled(true);

  } catch (const std::exception &e) {
    qDebug() << "Exception caught: " << e.what();
  }
}

void MainWindow::on_btnSolveMaze_clicked() {
  try {
    MazeSolver mazeSolver;

    const int start_x = ui->start_x->value();
    const int start_y = ui->start_y->value();
    const int end_x = ui->end_x->value();
    const int end_y = ui->end_y->value();

    if (start_x == end_x && start_y == end_y) {
      throw std::runtime_error("Start and end coordinates are the same.");
    }

    std::pair<int, int> src(start_y - 1, start_x - 1); // начальные координаты
    std::pair<int, int> dest(end_y - 1, end_x - 1); // конечные координаты

    QString currentDir = QCoreApplication::applicationDirPath();

    std::string currentDirr = currentDir.toStdString();

    size_t foundPos = currentDirr.find("src/");
    std::string modifiedDir;

    if (foundPos != std::string::npos) {
      modifiedDir = currentDirr.substr(0, foundPos + 4);
    }

    mazeSolver.parseMaze(modifiedDir + "/examples/awd.txt");

    std::vector<std::vector<int>> wave = mazeSolver.findPath(src, dest);

    QVector<QPoint> path;
    for (size_t i = 0; i < wave.size(); ++i) {
      for (size_t j = 0; j < wave[i].size(); ++j) {
        if (wave[i][j] != -1) {
          path.append(QPoint(static_cast<int>(j), static_cast<int>(i)));
        }
      }
    }

    auto compareFunction = [&](const QPoint &point1, const QPoint &point2) {
      return wave[point1.y()][point1.x()] < wave[point2.y()][point2.x()];
    };

    std::sort(path.begin(), path.end(), compareFunction);

    ui->maze->setSolution(path);
  } catch (const std::exception &e) {
    QMessageBox::critical(this, "Error", e.what());
  }
}

void MainWindow::on_spinBoxRows_valueChanged(int arg1) {
  ui->end_y->setMaximum(arg1);
}

void MainWindow::on_spinBoxCols_valueChanged(int arg1) {
  ui->end_x->setMaximum(arg1);
}

void MainWindow::on_btnLoadMazeFromFile_clicked() {
  try {
    MazeSolver mazeSolver;

    QString filePath = QFileDialog::getOpenFileName(
        this, tr("Open Maze File"), "", tr("Text Files (*.txt)"));
    if (filePath.isEmpty()) {
      return;
    }
    std::string fileName = filePath.toStdString();

    Matrix loadedMatrix;
    QString currentDir = QCoreApplication::applicationDirPath();

    std::string currentDirr = currentDir.toStdString();

    size_t foundPos = currentDirr.find("src/");
    std::string modifiedDir;

    if (foundPos != std::string::npos) {
      modifiedDir = currentDirr.substr(0, foundPos + 4);
    }

    loadedMatrix.loadMaze(fileName, modifiedDir);
    ui->maze->setMatrix(loadedMatrix);

    ui->maze->loadMazeFromFile(filePath, modifiedDir);

    ui->maze->update();
    ui->btnSolveMaze->setEnabled(true);
    ui->spinBoxRows->setValue(loadedMatrix.getRows());
    ui->spinBoxCols->setValue(loadedMatrix.getColumns());
    ui->end_x->setValue(loadedMatrix.getColumns());
    ui->end_x->setMaximum(loadedMatrix.getColumns());
    ui->end_y->setValue(loadedMatrix.getRows());
    ui->end_y->setMaximum(loadedMatrix.getRows());
  } catch (const std::exception &e) {
    QMessageBox::critical(this, "Error", e.what());
  }
}
