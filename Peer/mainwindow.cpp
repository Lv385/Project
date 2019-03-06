#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	peer_(nullptr),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

	SetIpValidator();

	//ui_->pb_start->setEnabled(false);
	ui_->pb_send->setEnabled(false);

	ClientDAL::ClientDB cdb;
	QVector<QString> friend_logins = cdb.GetFriendsLogin();
	for (const QString& login : friend_logins)
	{
		ui_->combo_box_friends->addItem(login);
	}

	peer_ = new Peer(this, ui_->le_port_my->text().toUShort());

	connect(peer_, SIGNAL(SendMessageToUI(QString)), this, SLOT(AppendMessage(QString)));
	connect(peer_, SIGNAL(SendLog(QString)), this, SLOT(AppendLogMessage(QString)));

    
    /*connect(peer_, SIGNAL(SendMessageToUI(QString)), this, SLOT(AppendMessage(QString)));
	connect(peer_, SIGNAL(SendLog(QString)),		 this, SLOT(AppendLogMessage(QString)));*/
	connect(ui_->pb_start, SIGNAL(clicked()), this, SLOT(OnPbStartClicker()));
	connect(ui_->combo_box_friends, SIGNAL(currentIndexChanged(QString)), this, SLOT(AppendHistory()));
	connect(ui_->pb_send, SIGNAL(clicked()), this, SLOT(OnPbSendClicked()));
	connect(ui_->pb_login, SIGNAL(clicked()), this, SLOT(OnPbLoginClicked()));
	/*ui_->l_your_status->setVisible(false);
	ui_->label->setVisible(false);
	ui_->le_ip->setVisible(false);
	ui_->label_2->setVisible(false);
	ui_->le_port->setVisible(false);
	ui_->label_logs->setVisible(false);
	ui_->label_3->setVisible(false);
	ui_->le_port_my->setVisible(false);*/
}

void MainWindow::OnPbStartClicker()
{
	if (peer_->startListening(ui_->le_port_my->text().toUShort()))
	{
		ui_->l_your_status->setText(tr("The server is running on\n\nIP: %1\nport: %2\n")
			.arg(peer_->get_my_ip().toString())
			.arg(peer_->get_my_port()));
		ui_->pb_send->setEnabled(true);
	}

}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::SetIpValidator()
{
	QString ip_range = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
	QRegExp ip_regex("^" + ip_range
		+ "\\." + ip_range
		+ "\\." + ip_range
		+ "\\." + ip_range + "$");
	QRegExpValidator *ip_validator = new QRegExpValidator(ip_regex, this);
	ui_->le_ip->setValidator(ip_validator);
}

void MainWindow::AppendMessage(QString message)
{
    ui_->plainTextEdit->appendPlainText(message); //username by id + message zzz
}

void MainWindow::AppendHistory()
{
	ui_->plainTextEdit->clear();
	ClientDAL::ClientDB db;
	QString login = ui_->combo_box_friends->currentText();

	QVector<ClientDAL::Message> history = db.GetMessages(login);
	for (auto i : history)
	{
		if (login == db.GetLoginById(i.owner_id))
		{
			ui_->plainTextEdit->appendPlainText(i.time.toString() + '|' + '<' + login + ">: " + i.data);
		}
		else
		{
			ui_->plainTextEdit->appendPlainText(i.time.toString() + '|' + "<Me> : " + i.data);
			
		}
	}
}

void MainWindow::OnPbSendClicked()
{
	qDebug() << "clicked";
	peer_->set_receiver_ip  (QHostAddress(ui_->le_ip->text()));
    peer_->set_receiver_port(ui_->le_port->text().toUShort());

	ClientDAL::ClientDB cdb;
	QString selected_login = ui_->combo_box_friends->currentText();
    peer_->SendRequest(cdb.GetIDByLogin(selected_login) ,ui_->le_message->text());  //id + mes  zzz

	ui_->plainTextEdit_Log->appendPlainText("\\\\\\\\\\\\\\\\\\\\\\\\\\\\/");
}

void MainWindow::AppendLogMessage(QString message)
{
	ui_->plainTextEdit_Log->appendPlainText(message);
}

void MainWindow::OnPbLoginClicked()
{
	QString login = ui_->le_login->text();
	if (peer_->LogIn(login, ui_->le_password->text()))
	{		
		peer_->set_login(login);
		ui_->pb_start->setEnabled(true);
		ui_->pb_send->setEnabled (true);
	}
}
