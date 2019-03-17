#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "about.h"
#include "insertdialog.h"
#include "graphwidget.h"
#include "inputdialog.h"

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

    void on_actionOpen_2_triggered();

    void on_actionEnter_triggered();

    void emit_file_opened(QString file_path);

signals:
    void file_opened(QString file_path);

private:
    Ui::MainWindow *ui;
    GraphWidget* graph;
    std::string current_opened_file;
};

#endif // MAINWINDOW_H
