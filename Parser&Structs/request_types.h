#ifndef REQUEST_TYPES_H
#define REQUEST_TYPES_H

#include <QtGlobal>
#include <QString>
#include <QHostAddress>

enum class ClientRequest : quint8
{
	MESSAGE = 0,
	LOGIN,
	REGISTER,
	FRIEND_REQUEST,
	FRIENDSHIP_REJECTED, //client send this to server if AddFriend request declined
	FRIENDSHIP_ACCEPTED,
	ONLINE_UPDATE,
	LAST                                        // this should be last to avoid errors
};

enum class ServerRequests: quint8
{
	LOGIN_SUCCEED = (char)ClientRequest::LAST + 1, //not sure if good
	LOGIN_FAILED,

	REGISTER_SUCCEED,
	REGISTER_FAILED,

	FRIEND_REQUST_FAILED, // will be returned by server if FriendRequestInfo.other_login is not contained in db
	FRIEND_REQUEST_SUCCEED,// will signal out that server will try to send friend request to FriendRequestInfo.other_login

	FRIEND_UPDATE_INFO
};


struct LoginOrRegisterInfo
{
	QHostAddress ip;    // server should get it from socket // to fix!!
	quint16 port;
	quint32 id;
	QString password;
};

//struct Login
//{
//	QHostAddress ip;    // server should get it from socket // to fix!!
//	quint16 port;
//	quint id
//	QString password;
//};
//struct RegisterInfo
//{
//	QHostAddress ip;    // server should get it from socket // to fix!!
//	quint16 port;
//	QString login;
//	QString password;
//};

//sending to all friends on peer logined
struct FriendUpdateInfo
{
	QHostAddress ip;
	quint16 port;
	quint32 id;
};

//User that want to be a friend of other user should send this structure to server with FRIEND_REQUEST header
//Also this structure will be emmited by client to server in a case of frienship acceptance with FRIENDSHIP_ACCEPTED header;
struct FriendRequestInfo
{
	QString other_login; //login of a potentil friend
	QString login; 
	QString password; 
};

//This structure should be accepted by client from server. It holds data 
//of a person that are interested in friendship with this 
//structure receiver. After receiving this, user get options:
//accept or reject friendship. In a case of rejection
//user send empty request FRIENDSHIP_REJECTED. If friendship accepted -
//FriendRequestInfo should be sended to server (with FRIENDSHIP_ACCEPTED header), where:
//FriendRequestInfo.other_login = AddFriend.requester_login;
//FriendRequestInfo.login = your login
//FriendRequestInfo.password = your pass
struct AddFriend {
	QString requester_login;
	QHostAddress requester_ip;  
	quint16 requester_port;
};

struct IdPort
{
	quint32 id;
	quint16 port;
};
#endif // !REQUEST_TYPES_H
