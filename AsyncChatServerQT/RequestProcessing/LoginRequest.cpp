#include "LoginRequest.h"
LoginRequest::LoginRequest(QByteArray&A):AbstractRequest(A)
{
	
	log = Parser::ParseAsLoginOrRegisterInfo(A);
	
	//prepareResponse();
}

void LoginRequest::prepareResponse()
{
	//check user,= in db  and set t or f
	if (db.CheckUser(log.login, log.password) == true)
	{
		db.UpdateIPPort(log.login, log.ip.toString(), log.port);
		logcheck=true;
	}
	else
	{
		logcheck = false;
	}

}
bool LoginRequest::sendResponde(QTcpSocket * initByClient)
{
	//send enum answer to client
	if (logcheck == true)
	{
		//QString str=;
		QByteArray b =Parser::Message_ToByteArray(QString(quint8(ServerRequests::LOGIN_SUCCEED)));
		initByClient->write(b);
		initByClient->waitForBytesWritten(3000);
		initByClient->disconnectFromHost();
	}
	else
	{
		QByteArray b = Parser::Message_ToByteArray(QString(quint8(ServerRequests::LOGIN_FAILED)));
		initByClient->write(b);
		initByClient->waitForBytesWritten(3000);
		initByClient->disconnectFromHost();
	}
	return true;
}

//return - will responde with 0 if everything is done good or -1 if something failed
//receives - 0#userName#passWord
//switch(firstbyte)
