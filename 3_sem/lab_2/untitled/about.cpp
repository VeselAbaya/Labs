#include "about.h"
#include "ui_about.h"
#include <QDebug>
About::About(QWidget *parent) : QDialog(parent),
                                ui(new Ui::About) {
    ui->setupUi(this);
    ui->textBrowser->setSource(QString("task.html"));
    setWindowTitle("About");
}

About::~About() {
    delete ui;
}

void About::on_taskButton_clicked() {
    ui->textBrowser->setSource(QString("task.html"));
}

void About::on_helpButton_clicked() {
    ui->textBrowser->setSource(QString("help.html"));
}

void About::on_authorButton_clicked() {
    ui->textBrowser->setSource(QString("author.html"));
}
