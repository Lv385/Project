#ifndef REQUEST_TYPES_H
#define REQUEST_TYPES_H

#include <QHostAddress>
#include <QString>
#include <QtGlobal>

//NOTATION: 
//
//  HEADER,//+accompanying_structure(c->s) Initiator^,-src 
//
//  (c->s)||(s->c)- direction of data flow: client to server or server to client
//  Initiator - who initizlize sending this data. Communication works
//            ass request-response pairs. If some request initialize conection
//            it is denoted by 'I'(for example, as a result of user interaction). 
//            If data is response to some I request that I become it's 'Initiator'.
//            Sign '^' means that response don't come in the same session.
//  -src   - initial source of a response
//            
//            
enum RequestOwnerType : quint8 {
  ClientRequest = 0x0,
  ServerRequests = 0x80
};
//no more than 128 types
enum class ClientRequest : quint8 {
  MESSAGE = ClientRequest,
  LOGIN,//+LoginInfo(c->s)I,-user
  REGISTER,//+RegisterInfo(c->s)I,-user
  FRIEND_REQUEST,//+FriendRequestInfo(c->s)I,-user
  FRIENDSHIP_REJECTED,//+empty(c->s)ADD_FRIEND_REQUEST^; 
  FRIENDSHIP_ACCEPTED,//+FriendRequestInfo(c->s)ADD_FRIEND_REQUEST^;  
  ONLINE_UPDATE,
};

// no more than 128 types
enum class ServerRequests : quint8 {
  LOGIN_SUCCEED = ServerRequests,//empty(s->c)LOGIN
  LOGIN_FAILED,//empty(s->c)LOGIN

  REGISTER_SUCCEED,//+RegisterSuccessInfo(s->c)REGISTER
  REGISTER_FAILED,//empty(s->c)REGISTER

  //requested login - not found
  FRIEND_REQUEST_FAILED,//empty(s->c)FRIEND_REQUEST;   
  FRIEND_REQUEST_SUCCEED,//empty(s->c)FRIEND_REQUEST;
  ADD_FRIEND_REQUEST,//+AddFriendInfo(s->c)I,-FRIEND_REQUEST ; 

  //sending to all friends on peer logined
  FRIEND_UPDATE_INFO//+FriendUpdateInfo(s->c)I,-LOGIN ; 
};


//comes after LOGIN header (c->s)
struct LoginInfo {
  quint16 port;
  quint32 id;
  QString password;
};

// comes after REGISTER header (c->s)
struct RegisterInfo {
  quint16 port;
  QString login;
  QString password;
};

//comes after  FRIEND_UPDATE_INFO header (c->s)
struct FriendUpdateInfo {
  QHostAddress ip;
  quint16 port;
  quint32 id;
};

// User that want to be a friend of other user should send this structure to
// server with FRIEND_REQUEST header Also this structure will be emmited by
// client to server in a case of frienship acceptance with FRIENDSHIP_ACCEPTED
// header;

// comes after  FRIEND_REQUEST || FRIENDSHIP_ACCEPTED header (c->s)
struct FriendRequestInfo {
  QString other_login;  // login of a potentil friend
  QString login;
  QString password;
};

// This structure should be accepted by client from server. It holds data
// of a person that are interested in friendship with this
// structure receiver. After receiving this, user get options:
// accept or reject friendship. In a case of rejection
// user send empty request FRIENDSHIP_REJECTED (c->s). If friendship accepted -
// FriendRequestInfo should be sended to server (with FRIENDSHIP_ACCEPTED
// header), where: FriendRequestInfo.other_login = AddFriend.requester_login;
// FriendRequestInfo.login = your login
// FriendRequestInfo.password = your pass

//comes after ADD_FRIEND_REQUEST header (s->c)
struct AddFriendInfo {
  QString requester_login;
  QHostAddress requester_ip;
  quint16 requester_port;
};
// comes after REGISTER_SUCCEED header (s->c)
struct RegisterSuccessInfo {
  quint32 id;
};


struct IdPort {
  quint32 id;
  quint16 port;
};

struct Message {
  quint32 id;
  QString message;
};
#endif  // !REQUEST_TYPES_H
