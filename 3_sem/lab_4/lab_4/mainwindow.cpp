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

    Tree<char> tree;
    while(input.good()) {
        std::string str;
        input >> str;
        if (str != "") {
            if (str[0] == '(') {
                try {
                    std::stringstream{str} >> tree;
                    tree.print_leaves(output);
                    output << '\n';
                } catch (std::logic_error& err) {
                    output << err.what() << '\n';
                } catch (std::exception& err) {
                    output << "Something went wrong" << '\n';
                }
            } else
                output << "First bracket is necessary" << '\n';
        }
    }

    ui->output->append(QString(output.str().c_str()));
}

void MainWindow::on_actionAbout_triggered() {
    About about;
    about.exec();
}
