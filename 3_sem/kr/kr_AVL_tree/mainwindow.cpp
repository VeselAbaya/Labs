#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow) {
    ui->setupUi(this);
    graph = new GraphWidget;
    setCentralWidget(graph);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionAbout_triggered() {
    About about;
    about.exec();
}

void MainWindow::on_actionInsert_triggered() {
    InsertDialog* insertDialog = new InsertDialog(this);
    connect(insertDialog, SIGNAL(insertSignal(int)), graph, SLOT(insertNode(int)));

    insertDialog->show();
}
