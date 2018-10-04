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
    Stack<pair<char, size_t>> stack;
  size_t len = input.length();
  for (size_t i = 0; i != len; ++i) {
    switch (input[i]) {
        case '[':
        case '{':
        case '(':
        stack.push(make_pair(input[i], i+1));
      break;
        case ']':
          if (!stack.empty() && stack.top().first == '[')
            stack.pop();
          else
            return i + 1;
        break;
        case '}':
            if (!stack.empty() && stack.top().first == '{')
            stack.pop();
                else
            return i + 1;
        break;
        case ')':
          if (!stack.empty() && stack.top().first == '(')
            stack.pop();
          else
            return i + 1;
        break;
    }
  }

  if (stack.empty())
    return 0;
  else
    return stack.top().second;
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
    ui->output->clear();

    while (input.good()) {
        std::string brace_seq;
        std::getline(input, brace_seq);

        if (brace_seq != "") {
            size_t res = check_braces(brace_seq);
            if (res)
              output << res;
            else
              output << "Success";

            output << '\n';
        }
    }

    ui->output->append(QString(output.str().c_str()));
}

void MainWindow::on_actionAbout_triggered() {
    About about;
    about.exec();
}


/*
#include "stack.h"
#include <iostream>
#include <string>
#include <cassert>
#include <utility>

using namespace std;

int check_braces(string input) {
    Stack<pair<char, int>> stack;
  int len = input.length();
  int last_opened_index;
  for (int i = 0; i != len; ++i) {
    switch (input[i]) {
        case '[':
        case '{':
        case '(':
        stack.push(make_pair(input[i], i+1));
      break;
        case ']':
          if (!stack.empty() && stack.top().first == '[')
            stack.pop();
          else
            return i + 1;
        break;
        case '}':
            if (!stack.empty() && stack.top().first == '{')
            stack.pop();
                else
            return i + 1;
        break;
        case ')':
          if (!stack.empty() && stack.top().first == '(')
            stack.pop();
          else
            return i + 1;
        break;
    }
  }

  if (stack.empty())
    return 0;
  else
    return stack.top().second;
}

void check_unit_test() {
  assert(check_braces("([](){([])})") == 0);
    assert(check_braces("()[]}") == 5);
    assert(check_braces("{{[()]]") == 7);
    assert(check_braces("{{{[][][]") == 3);
    assert(check_braces("{*{{}") == 3);
    assert(check_braces("[[*") == 2);
    assert(check_braces("{*}") == 0);
    assert(check_braces("{{") == 2);
    assert(check_braces("{}") == 0);
    assert(check_braces("") == 0);
    assert(check_braces("}") == 1);
    assert(check_braces("*{}") == 0);
    assert(check_braces("{{{**[][][]") == 3);
}

int main() {
  // string input;
  // cin >> input;
  // int res = check_braces(input);
  // if (res)
  //   cout << res << endl;
  // else
  //   cout << "Success" << endl;
  // return 0;
}
*/
