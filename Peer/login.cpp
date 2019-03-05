#include "Login.h"

Login::Login(QWidget *parent)
	: QDialog(parent)
{
	ui_->setupUi(this);
	connect(ui_->pushButton, SIGNAL(clicked()), this, SLOT(OnPbLogInClicked()));
}

Login::~Login()
{
}

void Login::OnPbLogInClicked()
{
	//TODO: Add validation
	hide();
	main_window_ = new MainWindow(this);
	main_window_->show();
}