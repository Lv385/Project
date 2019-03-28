#include "mainwindow.h"
#include <iostream>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      // peer_(nullptr),
      ui_(new Ui::MainWindow),
      client_controller_(nullptr) {
  ui_->setupUi(this);

  client_controller_ = new ClientController(this);
  client_controller_->app_info_.remote_server_ip = ui_->le_server_ip->text();
  client_controller_->app_info_.remote_server_port =
      ui_->le_server_port->text().toUShort();
  client_controller_->app_info_.my_port =
      ui_->le_port->text().toUShort();

  SetIpValidator();

  // ui_->pb_start->setEnabled(false);
  ui_->pb_send->setEnabled(true);

  logger_ = ClientLogger::Instance();
  logger_->set_log_level(
      LogLevel::HIGH);  // u can switch levels of logging(NOLOG, LOW, HIGH)

  QVector<SQLDAL::Friend> friends = client_data_.get_friends();
  for (const SQLDAL::Friend& i : friends) {
    ui_->combo_box_friends->addItem(i.login);
  }

  // peer_ = new Peer(this, ui_->le_port_my->text().toUShort());

  if (ui_->rb_engineering->isChecked()) {
    OnRbEngineeringClicked();
  }
  //
  ////  connect(peer_, SIGNAL(SendMessageToUI(QString)),
  //           this, SLOT(AppendMessage(QString)));
  //  connect(peer_, SIGNAL(SendLog(QString)), this,
  //                 SLOT(AppendLogMessage(QString)));

  connect(ui_->pb_start, SIGNAL(clicked()), this, SLOT(OnPbStartClicker()));
  connect(ui_->combo_box_friends, SIGNAL(currentIndexChanged(QString)), this,
          SLOT(AppendHistory()));
  connect(ui_->pb_send, SIGNAL(clicked()), this, SLOT(OnPbSendClicked()));
  connect(ui_->pb_login, SIGNAL(clicked()), this, SLOT(OnPbLoginClicked()));
  connect(ui_->rb_simple, SIGNAL(clicked()), this, SLOT(OnRbSimpleClicked()));
  connect(ui_->rb_engineering, SIGNAL(clicked()), this,
          SLOT(OnRbEngineeringClicked()));

  connect(client_controller_, SIGNAL(MessageRecieved(unsigned)), this,
          SLOT(OnMessageRecieved(unsigned)));
  // CLIENT CONTROLLER
  /* connect(client_controller_, SIGNAL(SendMessageToUI(QString)),
                         this, SLOT(AppendMessage(QString)));
   connect(client_controller_, SIGNAL(SendLog(QString)),
                         this, SLOT(AppendLogMessage(QString)));*/
  friends_ = client_controller_->LoadFriends();
}

void MainWindow::OnPbStartClicker() { 
  client_controller_->Start();
}

MainWindow::~MainWindow() { delete ui_; }

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
  unsigned id;
  for (auto a : friends_)
    if (a.login == login) 
      id = a.id;

  QVector<SQLDAL::Message> history = client_controller_->LoadMessages(id);
  for (auto i : history) {
    if (login == client_data_.get_login_by_id(i.owner_id)) {
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
  // peer_->set_receiver_ip(QHostAddress(ui_->le_ip->text()));
  // peer_->set_receiver_port(ui_->le_port->text().toUShort());

  QString selected_login = ui_->combo_box_friends->currentText();
  // peer_->SendRequest(client_client_data_.get_id_by_login(selected_login),
  //     ui_->le_message->text());  // id + mes  zzz
  // PeerInfo
  for (auto a : friends_)
    if (a.login == selected_login)
      client_controller_->SendMessage(a, ui_->le_message->text());
}

void MainWindow::AppendLogMessage(const char* value, QString message) {
  ui_->plainTextEdit_Log->appendPlainText(value + message);
}

void MainWindow::OnPbLoginClicked() {
  // peer_->set_server_ip_port((QHostAddress(ui_->le_server_ip->text())),
  // ui_->le_server_port->text().toShort());

  QString login = ui_->le_login->text();
  quint32 id = client_data_.get_id_by_login(login);

  // peer_->set_login(login);
  // peer_->set_id(id);
  // if (peer_->LogIn(login, ui_->le_password->text()))
  {
    //->l_your_status->setText(tr("The server is running on\n\nIP:%1\nport:
    //%2//n").arg(peer_->get_my_ip().toString()) .arg(peer_->get_my_port()));
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
  ui_->pb_login->setGeometry(610, 330, 70, 30);
}
void MainWindow::OnMessageRecieved(unsigned id) {
  AppendHistory();
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