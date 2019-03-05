#pragma once

#include <QDialog>
#include "ui_Login.h"
#include "mainwindow.h"

class Login : public QDialog
{
	Q_OBJECT

public:
	Login(QWidget *parent = Q_NULLPTR);
	~Login();

private slots:
	void OnPbLogInClicked();

private:
	Ui::Login *ui_;
	MainWindow *main_window_;
};
