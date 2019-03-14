#include "logger.h"
#include "../Parser&Structs/parser.h"
#pragma once

void Logger::log(QByteArray& raw_data) {
  quint8 type = Parser::getRequestType(raw_data);
  switch (type) {
    case (quint8)ServerRequests::LOGIN_SUCCEED:
      qDebug() << "Server output: LOGIN_SUCCEED(" << type<<")+empty{}";
      break;
    case (quint8)ServerRequests::LOGIN_FAILED:
      qDebug() << "Server output: LOGIN_FAILED(" << type<<")+empty{}";
      break;
    case (quint8)ServerRequests::REGISTER_FAILED:
      qDebug() << "Server output: REGISTER_FAILED(" << type<<")+empty{}";
      break;
    case (quint8)ServerRequests::FRIEND_REQUEST_FAILED:
      qDebug() << "Server output: FRIEND_REQUEST_FAILED(" << type<<")+empty{}";
      break;
    case (quint8)ServerRequests::FRIEND_REQUEST_SUCCEED: {
      qDebug() << "Server output: FRIEND_REQUEST_SUCCEED(" << type<<")+empty{}";
      break;
    }
    case (quint8)ServerRequests::REGISTER_SUCCEED: {
      RegisterSuccessInfo out;
      out = Parser::ParseAsRegisterSuccessInfo(raw_data);
      qDebug() << "Server  output: REGISTER_SUCCEED(" << type
               << ")+RegisterSuccessInfo{ " << out.id << " }";
      break;
    }
    case (quint8)ServerRequests::ADD_FRIEND_REQUEST: {
      AddFriendInfo out;
      out = Parser::ParseAsAddFriendInfo(raw_data);
      qDebug() << "Server  output: ADD_FRIEND_REQUEST(" << type
               << ")+AddFriendInfo{ " << out.requester_ip << ", "
               << out.requester_login << ", " << out.requester_port << " }";
      break;
    }
    case (quint8)ServerRequests::FRIEND_UPDATE_INFO: {
      FriendUpdateInfo out;
      out = Parser::ParseAsFriendUpdateInfo(raw_data);
      qDebug() << "Server  output: FRIEND_UPDATE_INFO(" << type
               << ")+RegisterSuccessInfo{ " << out.id << ", " << out.ip << ", "
               << out.port << " }";
      break;
    }
  }
}
