#include "inputdialog.h"
#include "ui_inputdialog.h"

#include <QDebug>

InputDialog::InputDialog(std::string current_opened_file, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);

    textEdit = new QTextEdit(this);
    QPushButton* button = new QPushButton("Enter", this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(textEdit);
    layout->addWidget(button);
    setLayout(layout);

    qDebug() << "here";
    qDebug() << current_opened_file.c_str();
    if (!current_opened_file.empty()) {
        std::ifstream file(current_opened_file);
        std::string row;
        while (std::getline(file, row)) {
            if (row.empty())
                break;
            textEdit->append(QString::fromStdString(row));
        }
    }

    connect(button, SIGNAL(clicked()), this, SLOT(close_dialog()));
}

void InputDialog::close_dialog() {
    QString file_path = QDir::currentPath() + QString("/app-input-dialog-graph.txt");
    std::ofstream file(file_path.toStdString());
    file << textEdit->toPlainText().toStdString();
    file.flush();

    emit graph_entered(file_path);
    close();
}

InputDialog::~InputDialog()
{
    delete ui;
}
