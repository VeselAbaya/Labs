#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../bmp.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QFileDialog>
#include <vector>
#include <QHash>

#define DELTA 0.05

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_compress_button_clicked();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;

    Bmp_image* image;
    Bmp_image* compress_image;
    QGraphicsScene* scene;
    QGraphicsScene* scene_comress;
};

#endif // MAINWINDOW_H
