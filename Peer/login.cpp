#include "Login.h"

Login::Login(QWidget *parent)
	: QDialog(parent)
{
	ui->setupUi(this);
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(OnPbLogInClicked()));
}

Login::~Login()
{
}

void Login::OnPbLogInClicked()
{
	//TODO: Add validation
	hide();
	main_window = new MainWindow(this);
	main_window->show();
}