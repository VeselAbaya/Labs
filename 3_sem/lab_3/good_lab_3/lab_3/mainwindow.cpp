#include "mainwindow.h"
#include "ui_mainwindow.h"

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

size_t check_braces(string input) {
  Stack<char> stack;
  size_t len = input.length();
  size_t i;
  for (i = 0; i != len; ++i) {
    switch (input[i]) {
        case '[':
        case '{':
        case '(':
        stack.push(input[i]);
      break;
        case ']':
          if (!stack.empty() && stack.top()==  '[')
            stack.pop();
          else
            return i + 1;
        break;
        case '}':
            if (!stack.empty() && stack.top() == '{')
            stack.pop();
                else
            return i + 1;
        break;
        case ')':
          if (!stack.empty() && stack.top() == '(')
            stack.pop();
          else
            return i + 1;
        break;
    }
  }

  if (stack.empty())
    return 0;
  else
    return i;
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

    while (input.good()) {
        std::string brace_seq;
        std::getline(input, brace_seq);

//        if (brace_seq != "") {
            size_t res = check_braces(brace_seq);
            if (res)
              output << res;
            else
              output << "Success";

            output << '\n';
//        }
    }

    ui->output->append(QString(output.str().c_str()));
}

void MainWindow::on_actionAbout_triggered() {
    About about;
    about.exec();
}
