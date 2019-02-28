/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pb_send;
    QLineEdit *le_message;
    QPlainTextEdit *plainTextEdit;
    QLabel *l_your_status;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *le_port;
    QLineEdit *le_ip;
    QPlainTextEdit *plainTextEdit_Log;
    QLabel *label_logs;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(553, 575);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pb_send = new QPushButton(centralWidget);
        pb_send->setObjectName(QString::fromUtf8("pb_send"));
        pb_send->setGeometry(QRect(414, 300, 131, 31));
        le_message = new QLineEdit(centralWidget);
        le_message->setObjectName(QString::fromUtf8("le_message"));
        le_message->setGeometry(QRect(30, 309, 371, 21));
        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(30, 10, 371, 281));
        l_your_status = new QLabel(centralWidget);
        l_your_status->setObjectName(QString::fromUtf8("l_your_status"));
        l_your_status->setGeometry(QRect(420, 40, 111, 91));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(410, 200, 141, 92));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        le_port = new QLineEdit(layoutWidget);
        le_port->setObjectName(QString::fromUtf8("le_port"));

        formLayout->setWidget(3, QFormLayout::LabelRole, le_port);

        le_ip = new QLineEdit(layoutWidget);
        le_ip->setObjectName(QString::fromUtf8("le_ip"));

        formLayout->setWidget(1, QFormLayout::LabelRole, le_ip);

        plainTextEdit_Log = new QPlainTextEdit(centralWidget);
        plainTextEdit_Log->setObjectName(QString::fromUtf8("plainTextEdit_Log"));
        plainTextEdit_Log->setGeometry(QRect(30, 360, 371, 161));
        label_logs = new QLabel(centralWidget);
        label_logs->setObjectName(QString::fromUtf8("label_logs"));
        label_logs->setGeometry(QRect(410, 360, 47, 13));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 553, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pb_send->setText(QApplication::translate("MainWindow", "Send", nullptr));
        l_your_status->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label->setText(QApplication::translate("MainWindow", "Enter IP", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Enter port", nullptr));
        le_port->setText(QApplication::translate("MainWindow", "8989", nullptr));
        le_ip->setText(QApplication::translate("MainWindow", "127.0.0.1", nullptr));
        label_logs->setText(QApplication::translate("MainWindow", "logs", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
