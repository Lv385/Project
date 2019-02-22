#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    ui->le_ip->setValidator(ipValidator);



    peer = new Peer(this);
    ui->l_your_status->setText(tr("The server is running on\n\nIP: %1\nport: %2\n")
                               .arg(peer->get_my_IP())
                               .arg(peer->get_receiver_server()->serverPort()));
    connect(peer, SIGNAL(sendMessageToUI(QString)), this, SLOT(appendMessage(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::appendMessage(QString message)
{
    ui->plainTextEdit->appendPlainText(message);
}

void MainWindow::on_pb_send_clicked()
{
    peer->set_receiver_IP(ui->le_ip->text());
    peer->set_receiver_port(ui->le_port->text());
    peer->sendMessage(ui->le_message->text());
}
