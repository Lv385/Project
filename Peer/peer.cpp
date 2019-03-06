#include "peer.h"


Peer::Peer(QObject *parent, quint16 listen_port)
        : QObject(parent)
		, server_ip_(QHostAddress(QString("192.168.103.102")))       //hardcode Olegs pc)
		, server_port_(8888)
		, my_listen_port_(listen_port)
		, udp_group_address_(QStringLiteral("239.255.43.21"))
		, server_connection_ (nullptr)

{
	tcp_server_ = new TcpServer(this, server_ip_, server_port_);
	is_active_ = true;

	qDebug() << "started listening on: " + QString::number(my_listen_port_);

	ClientDAL::ClientDB db;
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


	//BD

	//ClientDB testBD;

    //in_.setDevice(tcp_socket_);

	emit SendLog("My IP: " + my_ip_.toString());

    connect(tcp_server_, SIGNAL(NewConnection(Connection*)), this, SLOT(SetSocket(Connection*)));
    connect(tcp_server_, SIGNAL(NewServerConnection(Connection*)), this, SLOT(OnServerConnected(Connection*))); 
    connect(&update_info_timer_, &QTimer::timeout, this, &Peer::SendUpdateInfo);
    connect(&update_receiver_, &QUdpSocket::readyRead, this, &Peer::UpdateFriendsInfo);

	//connect(receiver_socket_, SIGNAL(error()),this, SLOT(DisplayError())); //for future errors

    //cannot catch this signal
}

void Peer::set_login(QString login)
{
	my_login_ = login;
}

void Peer::set_id(quint32 id)
{
	my_id_ = id;
}

bool Peer::is_active()
{
	return is_active_;
}

bool Peer::startListening(quint16 listen_port)
{
	my_listen_port_ = listen_port;
	tcp_server_->close();
	if (!tcp_server_->listen(QHostAddress::Any, my_listen_port_))
	{
		qDebug() << "cannot start on: " + QString::number(my_listen_port_);
		if (!tcp_server_->listen())
		{
			is_active_ = false;
			return false;
		}
		
	}

	update_sender_.bind(QHostAddress(QHostAddress::AnyIPv4), 0);
	update_receiver_.bind(QHostAddress::AnyIPv4, my_listen_port_, QUdpSocket::ReuseAddressHint);
	update_receiver_.joinMulticastGroup(udp_group_address_);
	update_info_timer_.start(3000);

	return true;
}


void Peer::SendRequest(unsigned id, QString message)
{
	if (connections_.find(id) == connections_.end())
	{
		connections_[id] = new Connection(this);
		ConnectToPeer(id);
	}
	
	if (connections_[id]->state() == QAbstractSocket::ConnectedState)
	{
		Message mes = { my_id_, message };
		connections_[id]->SendMessage(mes);
	}
}

//id zzz
bool Peer::ConnectToPeer(unsigned id)
{
	//tcp_socket_ = new QTcpSocket(this);
	ClientDAL::ClientDB cdb;
	QPair<QString, int> ip_port = cdb.GetIPPort(id); // marko - change to QPair<QString, quint16>  GetIPPort(const unsigned& user_id);
	connections_[id]->connectToHost(ip_port.first, ip_port.second);
	QString logMessage = receiver_ip_.toString() + " : " + QString::number(ip_port.second);
	emit SendLog("trying connect to: " + logMessage);
	if (connections_[id]->waitForConnected(5000))
	{
		emit SendLog("connected to:" + logMessage);
		//connect(tcp_socket_, SIGNAL(disconnected()), tcp_socket_, SLOT(deleteLater())); //woking with one socket so temporary commnent
		//connect(tcp_socket_, SIGNAL(destroyed()), this, SLOT(nullTcpSocket()));    
		//Connection* temp = connections_[2];
		connect(connections_[id], SIGNAL(readyRead()), connections_[id], SLOT(TryReadLine()));
		connect(connections_[id], SIGNAL(SendLog(QString)), this, SIGNAL(SendLog(QString)));
		connect(connections_[id], SIGNAL(SendMessageToUI(QString)), this, SIGNAL(SendMessageToUI(QString)));
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

void Peer::SendUpdateInfo()
{
	IdPort my_id_port;
	ClientDAL::ClientDB cdb;
	my_id_port.id = my_id_; // hardcode your own login
	my_id_port.port = my_listen_port_;

	QByteArray to_write = Parser::IdPort_ToByteArray(my_id_port); //pack 
	to_write.append(Parser::GetUnpossibleSequence());			  //append separator
	QString temp = udp_group_address_.toString();
	update_sender_.writeDatagram(to_write, udp_group_address_, my_listen_port_);
	emit SendLog("update sent");

	
}


void Peer::UpdateFriendsInfo()
{
	QByteArray datagram;
	IdPort updated_friend_info;
	ClientDAL::ClientDB cdb;

	// using QUdpSocket::readDatagram (API since Qt 4)
	while (update_receiver_.hasPendingDatagrams()) 
	{
		datagram.resize(int(update_receiver_.pendingDatagramSize()));
		QHostAddress peer_address;
		update_receiver_.readDatagram(datagram.data(), datagram.size(), &peer_address);
		updated_friend_info = Parser::ParseAsIdPort(datagram);
		if (updated_friend_info.id == my_id_)  // hardcode your own id
			continue;


		if (check_timers.find(updated_friend_info.id) == check_timers.end()) //zzz
		{
			cdb.SetFriendStatus(updated_friend_info.id, true);

			StatusTimer* timer = new StatusTimer();
			timer->set_id(updated_friend_info.id);
			timer->start(10000);        //set timer 10sec
			check_timers[timer->get_id()] = timer;
			connect(timer, &StatusTimer::TimeoutById, this, &Peer::SetOfflineStatus);
		}
		else
		{
			check_timers[updated_friend_info.id]->start(10000);  //reset timer
		}

		ClientDAL::ClientDB cdb;
		cdb.UpdateIPPort(updated_friend_info.id, peer_address.toString(), updated_friend_info.port); //:ffff change
		
		emit SendLog("updated " + cdb.GetLoginById(updated_friend_info.id) + "'s info");
	}
}


void Peer::SetOfflineStatus(quint32 id)
{
	ClientDAL::ClientDB cdb;
	cdb.SetFriendStatus(id, false);
	emit SendLog("set " + cdb.GetLoginById(id) + " offline status");

	StatusTimer* to_delete = check_timers[id];
	check_timers.remove(id);
	to_delete->deleteLater();
}

bool Peer::LogIn(QString login, QString password)
{
	ClientDAL::ClientDB cdb;

	server_connection_ = new Connection(this);
	connect(server_connection_, SIGNAL(SendLog(QString)), this, SIGNAL(SendLog(QString)));
	LoginOrRegisterInfo info;
	info.id = cdb.GetIDByLogin(login);
	info.password = password;
	info.ip = get_my_ip();
	info.port = get_my_port();

	QString test = server_ip_.toString();

	server_connection_->connectToHost(server_ip_, server_port_);

	if (!server_connection_->waitForConnected(4000))
	{
			return false;
	}
	if (!server_connection_->LoginRequest(info))
	{
		return false;
	}
	return true;
}

void Peer::SetSocket(Connection *connection)
{
	ClientDAL::ClientDB cdb;
	unsigned id = cdb.GetIDByIpPort(connection->peerAddress().toString(), connection->peerPort());


	connections_[id] = connection;

	connect(connection, SIGNAL(readyRead()), connection, SLOT(TryReadLine())); // try to read line to \n when recieving data
	connect(connection, SIGNAL(SendLog(QString)), this, SIGNAL(SendLog(QString)));
	connect(connection, SIGNAL(SendMessageToUI(QString)), this, SIGNAL(SendMessageToUI(QString)));
	

//	emit SendLog("setting socket: ");
		//don`t need old socket if having new connection

	emit SendLog("setting socket: " + QString::number(connection->localPort()));
	//connect(connection_, SIGNAL(readyRead()), connection_, SLOT(TryReadLine())); // try to read line to \n when recieving data
	//connect(connection_, SIGNAL(SendLog(QString)), this, SIGNAL(SendLog(QString)));
	//connect(connection_, SIGNAL(SendMessageToUI(QString)), this, SIGNAL(SendMessageToUI(QString))); to  return 
}

void Peer::nullTcpSocket()
{
}

void Peer::OnServerConnected(Connection * connection)
{
	server_connection_ = connection;
	connect(connection, SIGNAL(readyRead()), connection, SLOT(ServerWorker())); // try to read line to \n when recieving data
	connect(connection, SIGNAL(SendLog(QString)), this, SIGNAL(SendLog(QString)));
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


