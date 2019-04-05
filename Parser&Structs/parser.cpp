#include "parser.h"

QByteArray Parser::LoginInfo_ToByteArray(
   LoginInfo& login_or_register_info) {
  QByteArray result;
  QDataStream out(&result, QIODevice::WriteOnly);
  out << quint8(ClientRequest::LOGIN);               // type 
  out << login_or_register_info.port;                // port
  out << login_or_register_info.id;                  // id
  out << login_or_register_info.password;            // password
  return result;
}

LoginInfo Parser::ParseAsLoginInfo(QByteArray& data) {
  LoginInfo result;
  QDataStream in(&data, QIODevice::ReadOnly);
  quint8 type; 
  in >> type;
  in >> result.port;
  in >> result.id;
  in >> result.password; 
  return result;
}

QByteArray Parser::FriendRequestInfo_ToByteArray(FriendRequestInfo& friend_info, quint8 type) {
  QByteArray result;
  QDataStream out(&result, QIODevice::WriteOnly);
  out << quint8(type);  
  out << friend_info.id;                 
  out << friend_info.other_login;                    
  out << friend_info.password;                   
  return result;  
  
}

FriendRequestInfo Parser::ParseAsFriendRequestInfo(QByteArray& data) {
  FriendRequestInfo result;
  QDataStream in(&data, QIODevice::ReadOnly);
  quint8 type;
  in >> type;
  in >> result.id;
  in >> result.other_login;
  in >> result.password;
  return result;
}

QByteArray Parser::AddFriendInfo_ToByteArray(AddFriendInfo& add_friend_info) {
  QByteArray result;
  QDataStream out(&result, QIODevice::WriteOnly);
  out << quint8(ServerRequest::ADD_FRIEND_REQUEST);         // type
  out << add_friend_info.requester_login;                    // login
  out << add_friend_info.requester_id;                       // id

  return result;  
}

AddFriendInfo Parser::ParseAsAddFriendInfo(QByteArray& data) {
  AddFriendInfo result;
  QDataStream in(&data, QIODevice::ReadOnly);
  quint8 type;
  quint32 ip;  
  in >> type;
  in >> result.requester_login;
  in >> result.requester_id;
  return result;
}

QByteArray Parser::NewFriendInfo_ToByteArray(
  NewFriendInfo& friend_update_info) {
  QByteArray result;
  QDataStream out(&result, QIODevice::WriteOnly);
  out << quint8(ServerRequest::FRIEND_UPDATE_INFO);  // type
  out << friend_update_info.ip.toIPv4Address();       // ip
  out << friend_update_info.port;                     // port
  out << friend_update_info.id;                       // id
  out << friend_update_info.login;

  return result;
}




quint8 Parser::getRequestType(QByteArray& data) {
  quint8 result = data.data()[0];
  return result;
}

QByteArray Parser::ConnectInfo_ToByteArray(ConnectInfo& connect_info) {
  QByteArray result;
  QDataStream out(&result, QIODevice::WriteOnly);
  out << quint8(ClientClientRequest::CONNECT);  // type
  out << connect_info.id;                       // id
  return result;
}

ConnectInfo Parser::ParseAsConnectInfo(QByteArray& data) {
  ConnectInfo result;
  QDataStream in(&data, QIODevice::ReadOnly);
  quint8 type;
  in >> type;
  in >> result.id;
  return result;
}

QByteArray Parser::RegisterInfo_ToByteArray(RegisterInfo& register_info) {	  
  QByteArray result;
  QDataStream out(&result, QIODevice::WriteOnly);
  out << quint8(ClientRequest::REGISTER);               // type
  out << register_info.port;                            // port
  out << register_info.login;                           // login
  out << register_info.password;                        // password   
  return result;
}

RegisterInfo Parser::ParseAsRegisterInfo(QByteArray& data) {
  RegisterInfo result;
  QDataStream in(&data, QIODevice::ReadOnly);
  quint8 type;
  quint32 ip;  // port login password
  in >> type;
  in >> result.port;
  in >> result.login;
  in >> result.password;
  return result;
}

QByteArray Parser::RegisterSuccessInfo_ToByteArray(RegisterSuccessInfo& regis_info) {
  QByteArray result;
  QDataStream out(&result, QIODevice::WriteOnly);
  out << quint8(ServerRequest::REGISTER_SUCCEED);
  out << regis_info.id;  
  return result;  
}

RegisterSuccessInfo Parser::ParseAsRegisterSuccessInfo(QByteArray& data) {
  RegisterSuccessInfo result;
  QDataStream in(&data, QIODevice::ReadOnly);
  quint8 type;
  in >> type;
  in >> result.id;
  return result;
}



FriendUpdateInfo Parser::ParseAsFriendUpdateInfo(QByteArray& data) {
  FriendUpdateInfo result;
  QDataStream in(&data, QIODevice::ReadOnly);
  quint8 type;
  quint32 ip;
  in >> type;
  in >> ip;
  in >> result.port;
  in >> result.id;
  result.ip = QHostAddress(ip);

  return result;
}

QByteArray Parser::FriendUpdateInfo_ToByteArray(
    FriendUpdateInfo& friend_update_info) {
  QByteArray result;
  QDataStream out(&result, QIODevice::WriteOnly);
  out << quint8(ServerRequest::FRIEND_UPDATE_INFO);  // type
  out << friend_update_info.ip.toIPv4Address();       // ip
  out << friend_update_info.port;                     // port
  out << friend_update_info.id;                       // id
  return result;
}

NewFriendInfo Parser::ParseAsNewFriendInfo(QByteArray& data) {
  NewFriendInfo result;
  QDataStream in(&data, QIODevice::ReadOnly);
  quint8 type;
  quint32 ip;
  in >> type;
  in >> ip;
  in >> result.port;
  in >> result.id;
  in >> result.login;
  result.ip = QHostAddress(ip);

  return result;
}

QByteArray Parser::Message_ToByteArray(MessageInfo& message) {
  QByteArray result;
  QDataStream out(&result, QIODevice::WriteOnly);
  out << quint8(ClientClientRequest::MESSAGE);    // type
  out << message.message;                         // message
  return result;
}

MessageInfo Parser::ParseAsMessage(QByteArray& data) {
  MessageInfo result;
  QDataStream in(&data, QIODevice::ReadOnly);
  quint8 type;
  in >> type;                                     // type
  in >> result.message;                           // message
  return result;
}

QByteArray Parser::Empty_ToByteArray(quint8 type) {
  QByteArray result;
  QDataStream out(&result, QIODevice::WriteOnly);
  out << type;  // response
  return result;
}

QByteArray Parser::GetUnpossibleSequence() {
  QByteArray result;
  QDataStream out(&result, QIODevice::WriteOnly);
  quint16 unpossible = 0xFFFE;
  out << unpossible;
  return result;
}

QByteArray Parser::IdPort_ToByteArray(IdPort id_port) {
  QByteArray result;
  QDataStream out(&result, QIODevice::WriteOnly);
  out << quint8(ClientRequest::ONLINE_UPDATE);  // type
  out << id_port.id;                            // ip
  out << id_port.port;                          // port
  return result;
}

IdPort Parser::ParseAsIdPort(QByteArray& data) {
  IdPort result;

  QDataStream in(&data, QIODevice::ReadOnly);
  quint8 type;
  in >> type;
  in >> result.id;
  in >> result.port;

  return result;
}
