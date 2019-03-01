#include "peer.h"


Peer::Peer(QObject *parent)
        : QObject(parent)
        , tcp_server_(new QTcpServer(this))
        , tcp_socket_(new QTcpSocket(this))
{
    if (tcp_server_->listen(QHostAddress::Any, 8989)) //we can leave parameters empty
    {
		emit SendLog("Start listening on" + QString::number(8989));
    }
	else
	{
		//(tcpServer->errorString())); //error handling not implemented
		emit SendLog("cannot start listenig");
		return;
	}
	

	//ClientDB db;
	//db.AddNewFriend("admin", 1);


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


    //in_.setDevice(tcp_socket_);

	emit SendLog("My IP: " + my_ip_.toString());

    connect(tcp_server_, SIGNAL(newConnection()), this, SLOT(SetSocket())); // 
	//connect(receiver_socket_, SIGNAL(error()),this, SLOT(DisplayError())); //for future errors

    //cannot catch this signal
}

bool Peer::ConnectToPeer(QHostAddress receiver_ip, quint16 port)
{
	//tcp_socket_ = new QTcpSocket(this);
	tcp_socket_->connectToHost(receiver_ip_, port);
	QString logMessage = receiver_ip_.toString() + " : " + QString::number(port);
	emit SendLog("trying connect to: " + logMessage);
	if (tcp_socket_->waitForConnected(5000))
	{
		emit SendLog("connected to:" + logMessage);
		//connect(tcp_socket_, SIGNAL(disconnected()), tcp_socket_, SLOT(deleteLater())); //woking with one socket so temporary commnent
		//connect(tcp_socket_, SIGNAL(destroyed()), this, SLOT(nullTcpSocket()));         
		connect(tcp_socket_, SIGNAL(readyRead()), this, SLOT(TryReadLine()));
		return true;
	}
	else
	{
		emit SendLog("cannot connect to " + logMessage);
		//tcp_socket_->deleteLater();
		//tcp_socket_ = nullptr;
		return false;
	}
}


void Peer::SendMessage(QString message)
{
		if (tcp_socket_->state() == QAbstractSocket::UnconnectedState)
		{
			ConnectToPeer(receiver_ip_, receiver_port_);
		}
		if (tcp_socket_->state() == QAbstractSocket::ConnectedState)
		{
			//message += '\n';
			//qDebug() << "my server port: " << receiver_server_->serverPort();
			QString mes_log = "Me: " + tcp_socket_->localAddress().toString() + ':' + QString::number(tcp_socket_->localPort()) +
						   "\nPeer: " + tcp_socket_->peerAddress().toString() + ':' + QString::number(tcp_socket_->peerPort());
			emit SendLog(mes_log);
			message += '\0';

			tcp_socket_->write(message.toUtf8());
			emit SendLog("send");

			QString str = "->: " + message;
			emit SendMessageToUI(str);

			//receiver_socket_->close(); // calls disconnectFromHost which emits disconnected()
			//receiver_socket_ = nullptr;
			//m_sender_socket->disconnectFromHost();
		}
		else
		{
			QString str = QString("cannot coonect to") + receiver_ip_.toString() + ' : ' + QString::number(receiver_port_);
			emit SendLog(str);
			emit SendMessageToUI(str);
		}
}


void Peer::SetSocket()
{
//	emit SendLog("setting socket: ");

	tcp_socket_->deleteLater(); 	//don`t need old socket if having new connection
	if (tcp_server_->hasPendingConnections())
	{
		tcp_socket_ = tcp_server_->nextPendingConnection();
	}

	emit SendLog("setting socket: " + QString::number(tcp_socket_->localPort()));

	connect(tcp_socket_, SIGNAL(readyRead()), this, SLOT(TryReadLine())); // try to read line to \n when recieving data
}

void Peer::TryReadLine()
{
	QByteArray temp = tcp_socket_->readAll();
	if (temp.contains('\0'))
	{
		received_message_.append(temp);
		QString str = QString("<%1>: %2").arg(tcp_socket_->peerAddress().toString())
										 .arg(QString(received_message_));
		emit SendMessageToUI(str);
		received_message_.clear();
	}
	else
	{
		received_message_.append(temp);
	}		
	//if (tcp_socket_->canReadLine())
	//{
	//	QByteArray qba = tcp_socket_->readAll();

	//	received_message_ = qba;

	//	QString str = tr("<%1>: %2").arg(tcp_socket_->peerAddress().toString()).arg(QString(received_message_));

	//	emit SendMessageToUI(str);
	//}

}

void Peer::nullTcpSocket()
{
	tcp_socket_ = nullptr;
}

void Peer::ReadMessage() //not working should, look at TryReadLine()
{

	//qDebug() << "kek";
	//in_.startTransaction();

	//in_ >> received_message_;
	//
	//if (!in_.commitTransaction())
	//{
	//	return;
	//}
	//else
	//{
	//	QString str = tr("<%1>: %2").arg(receiver_socket_->peerAddress().toString()).arg(receiver_socket_);
	//	emit SendMessageToUI(str);

	//	receiver_socket_->disconnectFromHost();
	//}

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
