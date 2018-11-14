/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *taskButton;
    QPushButton *authorButton;
    QPushButton *helpButton;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QStringLiteral("About"));
        About->resize(600, 490);
        About->setMinimumSize(QSize(600, 490));
        About->setMaximumSize(QSize(600, 490));
        layoutWidget = new QWidget(About);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 601, 491));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        taskButton = new QPushButton(layoutWidget);
        taskButton->setObjectName(QStringLiteral("taskButton"));

        horizontalLayout->addWidget(taskButton);

        authorButton = new QPushButton(layoutWidget);
        authorButton->setObjectName(QStringLiteral("authorButton"));

        horizontalLayout->addWidget(authorButton);

        helpButton = new QPushButton(layoutWidget);
        helpButton->setObjectName(QStringLiteral("helpButton"));

        horizontalLayout->addWidget(helpButton);


        verticalLayout->addLayout(horizontalLayout);

        textBrowser = new QTextBrowser(layoutWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setSource(QUrl(QStringLiteral("qrc:/task.html")));

        verticalLayout->addWidget(textBrowser);


        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QApplication::translate("About", "Form", nullptr));
        taskButton->setText(QApplication::translate("About", "Task", nullptr));
        authorButton->setText(QApplication::translate("About", "Author", nullptr));
        helpButton->setText(QApplication::translate("About", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
