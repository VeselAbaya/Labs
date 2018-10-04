#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QFileDialog>
#include <QString>

#include <string>
#include <sstream>
#include <fstream>
#include <utility>

#include "about.h"
#include "stack.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();

    void on_button_clicked();

    void on_actionAbout_triggered();

private:
    std::stringstream input;
    std::stringstream output;
    QString input_file;
    QString output_file;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
