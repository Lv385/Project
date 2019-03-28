#ifndef PARSER_H
#define PARSER_H

#include <QByteArray>
#include <QDataStream>

#include "request_types.h"

class Parser {
 public:
  static quint8 getRequestType(QByteArray& data);
  
  static QByteArray ConnectInfo_ToByteArray(ConnectInfo& connect_info);
  static ConnectInfo ParseAsConnectInfo(QByteArray& data);

  static QByteArray Message_ToByteArray(Message& message);
  static Message ParseAsMessage(QByteArray& data);

  static QByteArray RegisterInfo_ToByteArray(RegisterInfo& register_info);
  static RegisterInfo ParseAsRegisterInfo(QByteArray& data);

  static QByteArray RegisterSuccessInfo_ToByteArray(RegisterSuccessInfo& regis_info);
  static RegisterSuccessInfo ParseAsRegisterSuccessInfo(QByteArray& data);

  static QByteArray LoginInfo_ToByteArray(LoginInfo& login_info);
  static LoginInfo ParseAsLoginInfo(QByteArray& data);

  static QByteArray FriendRequestInfo_ToByteArray(FriendRequestInfo& login_info, quint8 type);
  static FriendRequestInfo ParseAsFriendRequestInfo(QByteArray& data);  

  static QByteArray AddFriendInfo_ToByteArray(AddFriendInfo& login_info);
  static AddFriendInfo ParseAsAddFriendInfo(QByteArray& data);  

  static NewFriendInfo ParseAsNewFriendInfo(QByteArray& data);
  static QByteArray NewFriendInfo_ToByteArray(NewFriendInfo& new_friend_info);

  static QByteArray FriendUpdateInfo_ToByteArray(FriendUpdateInfo& friend_update_info);
  static FriendUpdateInfo ParseAsFriendUpdateInfo(QByteArray& data);
 
  static QByteArray GetUnpossibleSequence();
  // hardcode, this shoud be added to the end of any
  // QByteArray that is written by socket to awoid
  // erros hoping that this sequence will not appear
  // in any of our messages must be fixed
  static QByteArray Empty_ToByteArray(quint8 type);

  static QByteArray IdPort_ToByteArray(IdPort id_port);
  static IdPort ParseAsIdPort(QByteArray& data);
};

#endif  // PARSER_H
