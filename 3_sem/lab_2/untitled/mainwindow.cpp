#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setCentralWidget(ui->splitter);
    list = new h_list::s_expr;
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
}

void MainWindow::on_button_clicked() {
    input = std::stringstream(ui->input->toPlainText().toStdString());
    output = std::stringstream();

    while (input.good()) {
        std::string list_repr;
        std::getline(input, list_repr);

        if (list_repr != "") {
            std::istringstream list_repr_stream{list_repr};
            h_list::read_lisp(list, list_repr_stream);

            h_list::lisp flatten_list = h_list::flatten(list);
            h_list::write_lisp(flatten_list, output);

            output << '\n';
        }
    }

    ui->output->append(QString(output.str().c_str()));
}

void MainWindow::on_actionAbout_triggered() {
    About about;
    about.exec();
}
