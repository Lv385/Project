/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
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
    QLabel *l_your_status;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLineEdit *le_ip;
    QLabel *label_2;
    QLineEdit *le_port;
    QLabel *label;
    QPlainTextEdit *plainTextEdit_Log;
    QLabel *label_logs;
    QComboBox *combo_box_friends;
    QPushButton *pb_start;
    QWidget *layoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *label_3;
    QLineEdit *le_port_my;
    QPlainTextEdit *plainTextEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(735, 575);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pb_send = new QPushButton(centralWidget);
        pb_send->setObjectName(QString::fromUtf8("pb_send"));
        pb_send->setGeometry(QRect(550, 280, 131, 31));
        le_message = new QLineEdit(centralWidget);
        le_message->setObjectName(QString::fromUtf8("le_message"));
        le_message->setGeometry(QRect(30, 309, 491, 21));
        l_your_status = new QLabel(centralWidget);
        l_your_status->setObjectName(QString::fromUtf8("l_your_status"));
        l_your_status->setGeometry(QRect(550, 60, 141, 81));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(550, 170, 141, 92));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        le_ip = new QLineEdit(layoutWidget);
        le_ip->setObjectName(QString::fromUtf8("le_ip"));

        formLayout->setWidget(1, QFormLayout::LabelRole, le_ip);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        le_port = new QLineEdit(layoutWidget);
        le_port->setObjectName(QString::fromUtf8("le_port"));

        formLayout->setWidget(3, QFormLayout::LabelRole, le_port);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        plainTextEdit_Log = new QPlainTextEdit(centralWidget);
        plainTextEdit_Log->setObjectName(QString::fromUtf8("plainTextEdit_Log"));
        plainTextEdit_Log->setGeometry(QRect(30, 360, 491, 161));
        label_logs = new QLabel(centralWidget);
        label_logs->setObjectName(QString::fromUtf8("label_logs"));
        label_logs->setGeometry(QRect(560, 350, 101, 16));
        combo_box_friends = new QComboBox(centralWidget);
        combo_box_friends->setObjectName(QString::fromUtf8("combo_box_friends"));
        combo_box_friends->setGeometry(QRect(550, 30, 141, 22));
        pb_start = new QPushButton(centralWidget);
        pb_start->setObjectName(QString::fromUtf8("pb_start"));
        pb_start->setGeometry(QRect(540, 380, 141, 23));
        layoutWidget_2 = new QWidget(centralWidget);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(540, 410, 141, 92));
        formLayout_2 = new QFormLayout(layoutWidget_2);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

        le_port_my = new QLineEdit(layoutWidget_2);
        le_port_my->setObjectName(QString::fromUtf8("le_port_my"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, le_port_my);

        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(30, 20, 491, 271));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 735, 21));
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
        le_ip->setText(QApplication::translate("MainWindow", "127.0.0.1", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Enter host port", nullptr));
        le_port->setText(QApplication::translate("MainWindow", "8989", nullptr));
        label->setText(QApplication::translate("MainWindow", "Enter host IP", nullptr));
        label_logs->setText(QApplication::translate("MainWindow", "logs and testing", nullptr));
        pb_start->setText(QApplication::translate("MainWindow", "Start", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Enter your port to listen", nullptr));
        le_port_my->setText(QApplication::translate("MainWindow", "8989", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
