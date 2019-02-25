#include "peer.h"

Peer::Peer(QObject *parent)
        : QObject(parent)
        , receiver_server_(new QTcpServer(this))
        , receiver_socket_(new QTcpSocket(this))
{

    if (!receiver_server_->listen()) //we can leave parameters empty
    {
                //(tcpServer->errorString()));0
        return;
    }


	qDebug() << "my ip: " <<receiver_server_->serverAddress().toString();

    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    
	// use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            my_ip_ = ipAddressesList.at(i);
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (my_ip_.toString().isEmpty())
        my_ip_ = QHostAddress(QHostAddress::LocalHost);


    in_.setDevice(receiver_socket_);

	qDebug() <<" fjeriofr" <<my_ip_;

    connect(receiver_server_, &QTcpServer::newConnection, this, &Peer::SetReceiverSocket);

	// connect(sender_socket_, SIGNAL(error()),this, SLOT(DisplayError())); //for future errors

    //cannot catch this signal
    //connect(m_receiver_socket, &QIODevice::readyRead, this, &Peer::readMessage);	

    connect(receiver_socket_, &QAbstractSocket::disconnected, receiver_socket_, &QObject::deleteLater);
}

void Peer::SendMessage(QString message)
{
    sender_socket_ = new QTcpSocket(this);
    sender_socket_->connectToHost(receiver_ip_, receiver_port_.toInt());

    if (sender_socket_->waitForConnected()) //or make connect(... , SIGNAL(connected())...);)
    {
		qDebug() << "send";
		qDebug() << "my server port: "<< receiver_server_->serverPort(); 


        sender_socket_->write(message.toStdString().c_str());
        sender_socket_->waitForBytesWritten();  //bytesWritten() signal


        QString qstr = "->: " + message;
        emit SendMessageToUI(qstr);

        sender_socket_->close();
        //m_sender_socket->disconnectFromHost();
    }
	if(sender_socket_)
	{
		delete sender_socket_;
	}
}


void Peer::SetReceiverSocket()
{
    qDebug() << "setting RECIEVEd message";
    receiver_socket_ = receiver_server_->nextPendingConnection();

    //kostyl

    receiver_socket_->waitForReadyRead();
    QByteArray qba = receiver_socket_->readAll();

    received_message_ = qba;
    QString str = tr("<%1>: %2").arg(receiver_socket_->peerAddress().toString()).arg(received_message_);
    emit SendMessageToUI(str);
    receiver_socket_->disconnectFromHost();

    //end kostyl
}

void Peer::ReadMessage()
{
    //is not used
/*
    qDebug() << "kek";
    in.startTransaction();
    in >> m_received_message;

    if (!in.commitTransaction())
    {
        return;
    }
    else
    {
        QString str = tr("<%1>: %2").arg(m_receiver_socket->peerAddress().toString()).arg(m_received_message);
        emit sendMessageToUI(str);

        m_receiver_socket->disconnectFromHost();
    }
*/
}

void Peer::DisplayError(QAbstractSocket::SocketError socketError)
{
    /*
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(m_sender_socket->errorString()));
    }
    */
}

void Peer::set_receiver_port(const QString &receiver_port)
{
    receiver_port_ = receiver_port;
}

void Peer::set_receiver_ip(const QString &receiver_ip)
{
    receiver_ip_ = receiver_ip;
}




