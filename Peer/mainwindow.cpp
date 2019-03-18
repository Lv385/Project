#include "mainwindow.h"
#include <iostream>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), peer_(nullptr), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);

  SetIpValidator();
  ui_->pb_send->setEnabled(false);

  QVector<QString> friend_logins = client_dal_.GetFriendsLogin();
  for (const QString& login : friend_logins) {
    ui_->combo_box_friends->addItem(login);
  }
  
  peer_ = new Peer(this, ui_->le_port_my->text().toUShort());

  if (ui_->rb_engineering->isChecked()) {
    OnRbEngineeringClicked();
  }

  connect(peer_, SIGNAL(SendMessageToUI(QString)), 
           this, SLOT(AppendMessage(QString)));

  connect(ClientLogger::Instance(), SIGNAL(DisplayLog(const char*, QString)), this,
          SLOT(AppendLogMessage(const char*, QString)));

  connect(ui_->pb_start, SIGNAL(clicked()), 
                   this, SLOT(OnPbStartClicker()));
  connect(ui_->combo_box_friends, SIGNAL(currentIndexChanged(QString)), 
                            this, SLOT(AppendHistory()));
  connect(ui_->pb_send, SIGNAL(clicked()), 
                  this, SLOT(OnPbSendClicked()));
  connect(ui_->pb_login, SIGNAL(clicked()), 
                   this, SLOT(OnPbLoginClicked()));
  connect(ui_->rb_simple, SIGNAL(clicked()), 
                    this, SLOT(OnRbSimpleClicked()));
  connect(ui_->rb_engineering, SIGNAL(clicked()), 
                         this, SLOT(OnRbEngineeringClicked()));
}

void MainWindow::OnPbStartClicker() {
  peer_->set_server_ip_port((QHostAddress(ui_->le_server_ip->text())),
                            ui_->le_server_port->text().toShort());

  if (peer_->StartListening(ui_->le_port_my->text().toUShort())) {

    ui_->l_your_status->setText(
        tr("The server is running on\n\nIP: %1\nport: %2\n")
            .arg(peer_->get_my_ip().toString())
            .arg(peer_->get_my_port()));
    ui_->pb_send->setEnabled(true);
  }

  QString login = ui_->le_login->text();
  quint32 id = client_dal_.GetIDByLogin(login);

  peer_->set_login(login);
  peer_->set_id(id);
  /*if (peer_->LogIn(login, ui_->le_password->text()))
 {
       ui_->l_your_status->setText(tr("The server is running on\n\nIP:%1\nport:%2\n").arg(peer_->get_my_ip().toString()) .arg(peer_->get_my_port()));
 }*/
}

MainWindow::~MainWindow() {
  delete ui_;
}

void MainWindow::SetIpValidator() {
  QString ip_range = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
  QRegExp ip_regex("^" + ip_range + "\\." + ip_range + "\\." + ip_range +
                   "\\." + ip_range + "$");
  QRegExpValidator* ip_validator = new QRegExpValidator(ip_regex, this);
  ui_->le_ip->setValidator(ip_validator);
}

void MainWindow::AppendMessage(QString message) {
  ui_->plainTextEdit->appendPlainText(message);  // username by id + message
}

void MainWindow::AppendHistory() {
  ui_->plainTextEdit->clear();
  QString login = ui_->combo_box_friends->currentText();

  QVector<ClientDAL::Message> history = client_dal_.GetMessages(login);
  for (auto i : history) {
    if (login == client_dal_.GetLoginById(i.owner_id)) {
      ui_->plainTextEdit->appendPlainText(i.time.toString() + '|' + '<' +
                                          login + ">: " + i.data);
    } else {
      ui_->plainTextEdit->appendPlainText(i.time.toString() + '|' +
                                          "<Me> : " + i.data);
    }
  }
}

void MainWindow::OnPbSendClicked() {
  qDebug() << "clicked";
  peer_->set_receiver_ip(QHostAddress(ui_->le_ip->text()));
  peer_->set_receiver_port(ui_->le_port->text().toUShort());

  QString selected_login = ui_->combo_box_friends->currentText();
  peer_->SendRequest(client_dal_.GetIDByLogin(selected_login),
                     ui_->le_message->text());  // id + mes  zzz

  ui_->plainTextEdit_Log->appendPlainText("\\\\\\\\\\\\\\\\\\\\\\\\\\\\");
}


void MainWindow::AppendLogMessage(const char* value, QString message) {
  ui_->plainTextEdit_Log->appendPlainText(value + message);

}

void MainWindow::OnPbLoginClicked() {
  peer_->set_server_ip_port((QHostAddress(ui_->le_server_ip->text())),
    ui_->le_server_port->text().toShort());

  QString login = ui_->le_login->text();
  quint32 id = client_dal_.GetIDByLogin(login);
 
  peer_->set_login(login);
  peer_->set_id(id);
   if (peer_->LogIn(login, ui_->le_password->text()))
  {
  	ui_->l_your_status->setText(tr("The server is running on\n\nIP:%1\nport: %2\n").arg(peer_->get_my_ip().toString())
  		.arg(peer_->get_my_port()));
  }
}
void MainWindow::OnRbSimpleClicked() {
  ui_->l_your_status->setVisible(false);
  ui_->label->setVisible(false);
  ui_->le_ip->setVisible(false);
  ui_->label_2->setVisible(false);
  ui_->le_port->setVisible(false);
  ui_->label_logs->setVisible(false);
  ui_->label_3->setVisible(false);
  ui_->le_port_my->setVisible(false);
  ui_->plainTextEdit_Log->setVisible(false);
  ui_->pb_start->setVisible(false);
  ui_->le_server_ip->setVisible(false);
  ui_->le_server_port->setVisible(false);
  ui_->label_6->setVisible(false);
  ui_->label_7->setVisible(false);
  ui_->pb_login->setGeometry(610,330, 70, 30);
}
void MainWindow::OnRbEngineeringClicked() {
  ui_->l_your_status->setVisible(true);
  ui_->label->setVisible(true);
  ui_->le_ip->setVisible(true);
  ui_->label_2->setVisible(true);
  ui_->le_port->setVisible(true);
  ui_->label_logs->setVisible(true);
  ui_->label_3->setVisible(true);
  ui_->le_port_my->setVisible(true);
  ui_->plainTextEdit_Log->setVisible(true);
  ui_->pb_start->setVisible(true);
  ui_->le_server_ip->setVisible(true);
  ui_->le_server_port->setVisible(true);
  ui_->label_6->setVisible(true);
  ui_->label_7->setVisible(true);
  ui_->pb_login->setGeometry(630, 470, 70, 30);
}
