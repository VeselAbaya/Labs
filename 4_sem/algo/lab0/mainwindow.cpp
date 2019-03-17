#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow) {
    ui->setupUi(this);
    graph = new GraphWidget;
    setCentralWidget(graph);
    connect(this, SIGNAL(file_opened(QString)), graph, SLOT(file_opened(QString)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionAbout_triggered() {
    About about;
    about.exec();
}

void MainWindow::on_actionOpen_2_triggered() {
    QString input_file = QFileDialog::getOpenFileName(this, "Choose input file");
    emit_file_opened(input_file);
}

void MainWindow::on_actionEnter_triggered() {
    InputDialog* inputDialog = new InputDialog(current_opened_file);
    connect(inputDialog, SIGNAL(graph_entered(QString)), this, SLOT(emit_file_opened(QString)));
    inputDialog->exec();
}

void MainWindow::emit_file_opened(QString file_path) {
    current_opened_file = file_path.toStdString();
    emit file_opened(file_path);
}
