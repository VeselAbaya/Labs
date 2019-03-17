#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QDir>

#include <fstream>
#include <string>

namespace Ui {
class InputDialog;
}

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDialog(std::string current_opened_file, QWidget *parent = nullptr);
    ~InputDialog();

private slots:
    void close_dialog();

signals:
    void graph_entered(QString file_path);

private:
    Ui::InputDialog *ui;
    QTextEdit* textEdit;
};

#endif // INPUTDIALOG_H
