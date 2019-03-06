#include "LoginRequest.h"
LoginRequest::LoginRequest(QByteArray&A):AbstractRequest(A)
{
	
	//log = Parser::ParseAsLoginOrRegisterInfo(A);
	
	//prepareResponse();
}

LoginRequest::LoginRequest(QByteArray & A, DAL * d):AbstractRequest(A, d)
{
	log_ = Parser::ParseAsLoginOrRegisterInfo(A);
	prepareResponse();
}

void LoginRequest::prepareResponse()
{
	//check user,= in db  and set t or f
	requester_ = database->getClient(log_.id);
	if (requester_.getUserName().length() > 1) {
		requester_.setUserIp(log_.ip);
		requester_.setUserPort(log_.port);

		database->setClient(requester_);
		logcheck = true;
	} else {
		logcheck = false;
	}

	/*
	if (db.CheckUser(log.login, log.password) == true)
	{
		db.UpdateIPPort(log.login, log.ip.toString(), log.port);
		logcheck=true;
	}
	else
	{
		logcheck = false;
	}
	*/

}
bool LoginRequest::sendResponde(QTcpSocket * initByClient)
{
	//send enum answer to client
	if (logcheck == true)
	{
		//QString str=;
		QByteArray b = Parser::yesNoResponseToByteArray((quint8)ServerRequests::LOGIN_SUCCEED);
		b.append(Parser::GetUnpossibleSequence());
		initByClient->write(b);
		initByClient->waitForBytesWritten(3000);
		initByClient->disconnectFromHost();

		
		Client updatedClient = database->getClient(requester_.getUserName());
		toSend_.id = updatedClient.getUserId();
		toSend_.ip = updatedClient.getUserIp();
		toSend_.port = updatedClient.getUserPort();

		QByteArray raw_data = Parser::FriendUpdateInfo_ToByteArray(toSend_);
		raw_data.append(Parser::GetUnpossibleSequence());

		QVector<unsigned int> currentFriends = updatedClient.getFriends();
		QTcpSocket output_socket;
		for (unsigned i = 0; i < currentFriends.size(); i++) {
			Client tempClient = database->getClient(currentFriends[i]);
			output_socket.connectToHost(tempClient.getUserIp(), tempClient.getUserPort());
			if (output_socket.waitForConnected(5000)) {
				output_socket.write(raw_data);
				output_socket.waitForBytesWritten(1000);
				output_socket.disconnectFromHost();
			}
		}
		output_socket.close();
	}
	else
	{
		QByteArray b = Parser::yesNoResponseToByteArray((quint8)ServerRequests::LOGIN_FAILED);
		b.append(Parser::GetUnpossibleSequence());
		initByClient->write(b);
		initByClient->waitForBytesWritten(3000);
		initByClient->disconnectFromHost();
	}
	return true;
}

//return - will responde with 0 if everything is done good or -1 if something failed
//receives - 0#userName#passWord
//switch(firstbyte)
