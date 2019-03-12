#ifndef PARSER_H
#define PARSER_H

#include <QByteArray>
#include <QDataStream>

#include "request_types.h"

class Parser {
 public:
  static quint8 getRequestType(QByteArray& data);

  static QByteArray RegisterInfo_ToByteArray(Registration& regis_info);
  static Registration ParseAsRegisterInfo(QByteArray& data);

  static LoginOrRegisterInfo ParseAsLoginOrRegisterInfo(QByteArray& data);
  static QByteArray LoginOrRegisterInfo_ToByteArray(
    LoginOrRegisterInfo& login_info);

  static FriendUpdateInfo ParseAsFriendUpdateInfo(QByteArray& data);
  static QByteArray FriendUpdateInfo_ToByteArray(
    FriendUpdateInfo& friend_update_info);

  static QByteArray Message_ToByteArray(Message& message);
  static Message ParseAsMessage(QByteArray& data);

  static QByteArray GetUnpossibleSequence();
  // hardcode, this shoud be added to the end of any
  // QByteArray that is written by socket to awoid
  // erros hoping that this sequence will not appear
  // in any of our messages must be fixed
  static QByteArray yesNoResponseToByteArray(quint8 type);

  static QByteArray IdPort_ToByteArray(IdPort id_port);
  static IdPort ParseAsIdPort(QByteArray& data);
};

#endif  // PARSER_H
