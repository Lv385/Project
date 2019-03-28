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
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
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
    QLabel *label;
    QLineEdit *le_port;
    QPlainTextEdit *plainTextEdit_Log;
    QLabel *label_logs;
    QComboBox *combo_box_friends;
    QPushButton *pb_start;
    QWidget *layoutWidget_2;
    QFormLayout *formLayout_2;
    QLineEdit *le_port_my;
    QLabel *label_3;
    QPlainTextEdit *plainTextEdit;
    QLineEdit *le_login;
    QLineEdit *le_password;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pb_login;
    QRadioButton *rb_simple;
    QRadioButton *rb_engineering;
    QLineEdit *le_server_ip;
    QLineEdit *le_server_port;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *pb_register;
    QPushButton *pb_add_friend;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(787, 575);
        MainWindow->setFocusPolicy(Qt::TabFocus);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow{\n"
"background-color:#1d1d1d\n"
"}\n"
"QLabel{\n"
"color:#fff;\n"
"}\n"
"QRadioButton{\n"
"color:#fff;\n"
"}\n"
"QLineEdit{\n"
"color:#fff;\n"
" border-radius: 6;\n"
"border:none;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pb_send = new QPushButton(centralWidget);
        pb_send->setObjectName(QString::fromUtf8("pb_send"));
        pb_send->setGeometry(QRect(470, 340, 70, 30));
        pb_send->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    color: #b1b1b1;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-width: 1px;\n"
"    border-color: #1e1e1e;\n"
"    border-style: solid;\n"
"    border-radius: 10;\n"
"    padding: 3px;\n"
"    font-size: 12px;\n"
"    padding-left: 5px;\n"
"    padding-right: 5px;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929, stop: 0.9 #282828, stop: 1 #252525);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QPushButton:focus {\n"
"    /*background-color: red;*/\n"
"}"));
        le_message = new QLineEdit(centralWidget);
        le_message->setObjectName(QString::fromUtf8("le_message"));
        le_message->setGeometry(QRect(30, 340, 411, 21));
        le_message->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"color:#ffffff;\n"
" background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-radius: 10;\n"
"}\n"
""));
        l_your_status = new QLabel(centralWidget);
        l_your_status->setObjectName(QString::fromUtf8("l_your_status"));
        l_your_status->setGeometry(QRect(490, 60, 141, 81));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(460, 380, 141, 86));
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

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        le_port = new QLineEdit(layoutWidget);
        le_port->setObjectName(QString::fromUtf8("le_port"));

        formLayout->setWidget(3, QFormLayout::LabelRole, le_port);

        plainTextEdit_Log = new QPlainTextEdit(centralWidget);
        plainTextEdit_Log->setObjectName(QString::fromUtf8("plainTextEdit_Log"));
        plainTextEdit_Log->setGeometry(QRect(30, 380, 411, 141));
        plainTextEdit_Log->setStyleSheet(QString::fromUtf8("QPlainTextEdit{\n"
"color:#ffffff;\n"
" background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-radius: 20;\n"
"}"));
        label_logs = new QLabel(centralWidget);
        label_logs->setObjectName(QString::fromUtf8("label_logs"));
        label_logs->setGeometry(QRect(230, 360, 101, 16));
        combo_box_friends = new QComboBox(centralWidget);
        combo_box_friends->setObjectName(QString::fromUtf8("combo_box_friends"));
        combo_box_friends->setGeometry(QRect(470, 310, 131, 22));
        combo_box_friends->setStyleSheet(QString::fromUtf8("QComboBox{\n"
"    color: #fff;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-width: 1px;\n"
"    border-color: #1e1e1e;\n"
"    border-style: solid;\n"
"    border-radius: 6;\n"
"    padding: 3px;\n"
"    font-size: 12px;\n"
"    padding-left: 5px;\n"
"    padding-right: 5px;\n"
"}\n"
"QComboBox::item{\n"
"    color: #b1b1b1;\n"
"	background-color:#1d1d1d;	\n"
"}\n"
"QComboBox::item:selected{\n"
"    color: #b1b1b1;\n"
"}\n"
""));
        pb_start = new QPushButton(centralWidget);
        pb_start->setObjectName(QString::fromUtf8("pb_start"));
        pb_start->setGeometry(QRect(680, 110, 70, 30));
        pb_start->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    color: #b1b1b1;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-width: 1px;\n"
"    border-color: #1e1e1e;\n"
"    border-style: solid;\n"
"    border-radius: 10;\n"
"    padding: 3px;\n"
"    font-size: 12px;\n"
"    padding-left: 5px;\n"
"    padding-right: 5px;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929, stop: 0.9 #282828, stop: 1 #252525);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QPushButton:focus {\n"
"    /*background-color: red;*/\n"
"}"));
        layoutWidget_2 = new QWidget(centralWidget);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(460, 480, 141, 41));
        formLayout_2 = new QFormLayout(layoutWidget_2);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        le_port_my = new QLineEdit(layoutWidget_2);
        le_port_my->setObjectName(QString::fromUtf8("le_port_my"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, le_port_my);

        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(30, 20, 411, 311));
        plainTextEdit->setStyleSheet(QString::fromUtf8("QPlainTextEdit{\n"
"color:#ffffff;\n"
" background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"  border-radius: 20;\n"
"}"));
        le_login = new QLineEdit(centralWidget);
        le_login->setObjectName(QString::fromUtf8("le_login"));
        le_login->setGeometry(QRect(510, 160, 131, 20));
        le_password = new QLineEdit(centralWidget);
        le_password->setObjectName(QString::fromUtf8("le_password"));
        le_password->setGeometry(QRect(510, 190, 131, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(450, 160, 47, 13));
        label_4->setStyleSheet(QString::fromUtf8(""));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(450, 190, 47, 13));
        pb_login = new QPushButton(centralWidget);
        pb_login->setObjectName(QString::fromUtf8("pb_login"));
        pb_login->setGeometry(QRect(680, 160, 70, 30));
        pb_login->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    color: #b1b1b1;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-width: 1px;\n"
"    border-color: #1e1e1e;\n"
"    border-style: solid;\n"
"    border-radius: 10;\n"
"    padding: 3px;\n"
"    font-size: 12px;\n"
"    padding-left: 5px;\n"
"    padding-right: 5px;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929, stop: 0.9 #282828, stop: 1 #252525);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QPushButton:focus {\n"
"    /*background-color: red;*/\n"
"}"));
        rb_simple = new QRadioButton(centralWidget);
        rb_simple->setObjectName(QString::fromUtf8("rb_simple"));
        rb_simple->setGeometry(QRect(600, 20, 82, 17));
        rb_engineering = new QRadioButton(centralWidget);
        rb_engineering->setObjectName(QString::fromUtf8("rb_engineering"));
        rb_engineering->setGeometry(QRect(460, 20, 111, 17));
        rb_engineering->setStyleSheet(QString::fromUtf8(""));
        rb_engineering->setChecked(true);
        le_server_ip = new QLineEdit(centralWidget);
        le_server_ip->setObjectName(QString::fromUtf8("le_server_ip"));
        le_server_ip->setGeometry(QRect(610, 400, 106, 16));
        le_server_port = new QLineEdit(centralWidget);
        le_server_port->setObjectName(QString::fromUtf8("le_server_port"));
        le_server_port->setGeometry(QRect(610, 440, 106, 16));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(610, 380, 81, 16));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(610, 420, 91, 16));
        pb_register = new QPushButton(centralWidget);
        pb_register->setObjectName(QString::fromUtf8("pb_register"));
        pb_register->setGeometry(QRect(680, 200, 75, 23));
        pb_add_friend = new QPushButton(centralWidget);
        pb_add_friend->setObjectName(QString::fromUtf8("pb_add_friend"));
        pb_add_friend->setGeometry(QRect(680, 230, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 787, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MesX", nullptr));
        pb_send->setText(QApplication::translate("MainWindow", "Send", nullptr));
        l_your_status->setText(QString());
        le_ip->setText(QApplication::translate("MainWindow", "127.0.0.1", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Enter host port", nullptr));
        label->setText(QApplication::translate("MainWindow", "Enter host IP", nullptr));
        le_port->setText(QApplication::translate("MainWindow", "8989", nullptr));
        label_logs->setText(QApplication::translate("MainWindow", "logs and testing", nullptr));
        pb_start->setText(QApplication::translate("MainWindow", "Start", nullptr));
        le_port_my->setText(QApplication::translate("MainWindow", "8989", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Enter your port to listen", nullptr));
        le_login->setText(QApplication::translate("MainWindow", "liubomyr", nullptr));
        le_password->setText(QApplication::translate("MainWindow", "password", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Login", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Password", nullptr));
        pb_login->setText(QApplication::translate("MainWindow", "Log In", nullptr));
        rb_simple->setText(QApplication::translate("MainWindow", "Simple mode", nullptr));
        rb_engineering->setText(QApplication::translate("MainWindow", "Engineering mode", nullptr));
        le_server_ip->setText(QApplication::translate("MainWindow", "192.168.103.121", nullptr));
        le_server_port->setText(QApplication::translate("MainWindow", "8888", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Enter server IP", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Enter server port", nullptr));
        pb_register->setText(QApplication::translate("MainWindow", "Register", nullptr));
        pb_add_friend->setText(QApplication::translate("MainWindow", "Add friend", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
