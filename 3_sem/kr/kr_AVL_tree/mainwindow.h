#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "about.h"
#include "insertdialog.h"
#include "graphwidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAbout_triggered();

    void on_actionInsert_triggered();

private:
    Ui::MainWindow *ui;
    GraphWidget* graph;
};

#endif // MAINWINDOW_H
