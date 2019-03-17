#include "insertdialog.h"
#include "ui_insertdialog.h"

InsertDialog::InsertDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertDialog)
{
    ui->setupUi(this);
}

InsertDialog::~InsertDialog() {
    delete ui;
}

void InsertDialog::on_insertButton_clicked() {
//    emit insertSignal(ui->textEdit->toPlainText()));
}
