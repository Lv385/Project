#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    QString ip_range = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ip_regex ("^" + ip_range
                     + "\\." + ip_range
                     + "\\." + ip_range
                     + "\\." + ip_range + "$");
    QRegExpValidator *ip_validator = new QRegExpValidator(ip_regex, this);
    ui_->le_ip->setValidator(ip_validator);



    peer_ = new Peer(this);

	connect(peer_, SIGNAL(SendMessageToUI(QString)), this, SLOT(AppendMessage(QString)));
	connect(peer_, SIGNAL(SendLog(QString)),		 this, SLOT(AppendLogMessage(QString)));

    ui_->l_your_status->setText(tr("The server is running on\n\nIP: %1\nport: %2\n")
                               .arg(peer_->get_my_ip().toString())
                               .arg(peer_->get_my_port()));
    /*connect(peer_, SIGNAL(SendMessageToUI(QString)), this, SLOT(AppendMessage(QString)));
	connect(peer_, SIGNAL(SendLog(QString)),		 this, SLOT(AppendLogMessage(QString)));*/

	connect(ui_->pb_send, SIGNAL(clicked()), this, SLOT(OnPbSendClicked()));
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::AppendMessage(QString message)
{
    ui_->plainTextEdit->appendPlainText(message);
}

void MainWindow::OnPbSendClicked()
{
	qDebug() << "clicked";
	peer_->set_receiver_ip  (QHostAddress(ui_->le_ip->text()));
    peer_->set_receiver_port(ui_->le_port->text().toUShort());
    peer_->SendMessage(ui_->le_message->text());

	ui_->plainTextEdit_Log->appendPlainText("\\\\\\\\\\\\\\\\\\\\\\\\\\\\/");

}

void MainWindow::AppendLogMessage(QString message)
{
	ui_->plainTextEdit_Log->appendPlainText(message);
}
