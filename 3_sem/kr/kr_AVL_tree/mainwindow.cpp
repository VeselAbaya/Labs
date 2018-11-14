#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->input->setFontPointSize(16);
    ui->output->setFontPointSize(16);
    setCentralWidget(ui->splitter);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionOpen_triggered() {
    input_file = QFileDialog::getOpenFileName(this, "Choose input file");
    std::ifstream file{input_file.toStdString()};
    while (file.good()) {
        std::string list_repr;
        file >> list_repr;
        input << list_repr << '\n';
    }

    ui->input->append(QString(input.str().c_str()));
}

void MainWindow::on_actionSave_triggered() {
    output_file = QFileDialog::getSaveFileName(this, "Choose output file");
    std::ofstream file{output_file.toStdString()};

    std::string output = ui->output->toPlainText().toStdString();
    if (file.good())
        file << output;

    file.close();
}

void MainWindow::on_button_clicked() {
    input = std::stringstream(ui->input->toPlainText().toStdString());
    output = std::stringstream();
    ui->output->clear();

    AVL_tree<int> tree;
    tree.insert(1);
    tree.insert(12);
    tree.insert(2);
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(345);
    tree.output(output);
    output << std::endl;
    tree.remove(2);
    tree.output(output);

    ui->output->append(QString(output.str().c_str()));
}

void MainWindow::on_actionAbout_triggered() {
    About about;
    about.exec();
}
