#pragma once
#include "logger.h"

void Logger::WriteLogToFile(QString& filename, QString& text) {
  QFile file(filename);
  if (file.open(QIODevice::Append | QIODevice::Text)) {
    QTextStream stream(&file);
    stream << text << endl;
    file.close();
  }
}

QString Logger::ConvertQuint8ToString(quint8 & num)
{
  QString tmp;
  return tmp.setNum(num);
}

void Logger::log(QByteArray raw_data) {
  if (ifLogingEnable) {
    
    QString outingString;  // date (d/m/y) time (h/m/s)
	QString txt = QDateTime::currentDateTime().toString("dd:MM:yyyy hh:mm:ss ");
    quint8 type = Parser::getRequestType(raw_data);
    switch (type) {
      case (quint8)ServerRequests::LOGIN_SUCCEED:
		outingString = "Server output: LOGIN_SUCCEED ( " + ConvertQuint8ToString(type) +
		  ")"+txt+"+ empty{}";
        qDebug() << outingString << "\n";
        WriteLogToFile(QString("LOG.txt"), outingString);
        break;
      case (quint8)ServerRequests::LOGIN_FAILED:
        outingString = "Server output: LOGIN_FAILED( " + ConvertQuint8ToString(type) +
                       ")" + txt + "+ empty{}";
        qDebug() << outingString << "\n";
		WriteLogToFile(QString("LOG.txt"), outingString);
        break;
      case (quint8)ServerRequests::REGISTER_FAILED:
        outingString = "Server output: REGISTER_FAILED( " + ConvertQuint8ToString(type) +
                       ")" + txt + "+ empty{}";
        qDebug() << outingString << "\n";
        WriteLogToFile(QString("LOG.txt"), outingString);
        break;
      case (quint8)ServerRequests::FRIEND_REQUEST_FAILED:
        outingString = "Server output: FRIEND_REQUEST_FAILED( " +
		  ConvertQuint8ToString(type) + ") " + txt + "+ empty{}";
        qDebug() << outingString << '\n';
        WriteLogToFile(QString("LOG.txt"), outingString);
        break;
      case (quint8)ServerRequests::FRIEND_REQUEST_SUCCEED: {
        outingString = "Server output: FRIEND_REQUEST_SUCCEED( " +
		  ConvertQuint8ToString(type) + ") " + txt + "+empty{}";
        qDebug() << outingString << "\n";
        WriteLogToFile(QString("LOG.txt"), outingString);
        break;
      }
      case (quint8)ServerRequests::REGISTER_SUCCEED: {
        RegisterSuccessInfo out;
        out = Parser::ParseAsRegisterSuccessInfo(raw_data);
        outingString = "Server  output: REGISTER_SUCCEED(" + ConvertQuint8ToString(type) +
                       ")+RegisterSuccessInfo{ " + QString(out.id) + " }" + txt+ '\n';

        qDebug() << outingString << "\n";
        WriteLogToFile(QString("LOG.txt"), outingString);
        break;
      }
      case (quint8)ServerRequests::ADD_FRIEND_REQUEST: {
        AddFriendInfo out;
        out = Parser::ParseAsAddFriendInfo(raw_data);
        outingString = "Server  output: ADD_FRIEND_REQUEST(" + ConvertQuint8ToString(type) +
                       +")+AddFriendInfo{ " + out.requester_ip.toString() +
                       ", " + out.requester_login + ", " +
                       QString(out.requester_port) + " }" + txt + '\n';
        qDebug() << outingString << "\n";
        WriteLogToFile(QString("LOG.txt"), outingString);
        break;
      }
      case (quint8)ServerRequests::FRIEND_UPDATE_INFO: {
        FriendUpdateInfo out;
        out = Parser::ParseAsFriendUpdateInfo(raw_data);
        outingString = "Server  output: FRIEND_UPDATE_INFO(" + ConvertQuint8ToString(type) +
                       ") + FriendUpdateInfo{ " + QString(out.id) + ", " +
                       out.ip.toString() + ", " + QString(out.port) + " }" + txt + '\n';
        qDebug() << outingString << "\n";
        WriteLogToFile(QString("LOG.txt"), outingString);
        break;
      }
    }
  }
}
