#include "about.h"
#include "ui_about.h"
#include <QDebug>

About::About(QWidget *parent) : QDialog(parent),
                                ui(new Ui::About) {
    ui->setupUi(this);
    ui->textBrowser->setSource(QString("qrc:/task.html"));
    setWindowTitle("About");
}

About::~About() {
    delete ui;
}

void About::on_taskButton_clicked() {
    ui->textBrowser->setSource(QString("qrc:/task.html"));
}

void About::on_helpButton_clicked() {
    ui->textBrowser->setSource(QString("qrc:/help.html"));
}

void About::on_authorButton_clicked() {
    ui->textBrowser->setSource(QString("qrc:/author.html"));
}
