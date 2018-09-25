#include "about.h"
#include "ui_about.h"
#include <QDebug>
About::About(QWidget *parent) : QDialog(parent),
                                ui(new Ui::About) {
    ui->setupUi(this);
    ui->textBrowser->setSource(QString("task.html"));
//    ui->textBrowser->setSearchPaths(QStringList() << ":/");
    setWindowTitle("About");
}

About::~About() {
    delete ui;
}
