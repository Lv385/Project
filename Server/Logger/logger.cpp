#pragma once
#include "logger.h"

void Logger::WriteLogToFile(QString& filename, QString& text) {
  
  QFile file(filename);
  if (file.open(QIODevice::ReadWrite)) {
	QTextStream stream(&file);
	stream << text << endl;
	file.close();
  }
  
}

void Logger::log(QByteArray& raw_data) {

  QDate date = QDate::currentDate(); 
  QString dateString = date.toString();
  QTime time = QTime::currentTime();
  QString timeString = time.toString();
  QString outingString ; // date (d/m/y) time (h/m/s) 

  quint8 type = Parser::getRequestType(raw_data);
  switch (type) {
    case (quint8)ServerRequests::LOGIN_SUCCEED:
	  outingString = "Server output: LOGIN_SUCCEED " + QString(type) + ") DATE: " + dateString + " TIME: " + timeString + "+empty{}\n";
	  qDebug() <<outingString<<"\n";
	  WriteLogToFile(QString("LOG.txt"), outingString);
	  break;
    case (quint8)ServerRequests::LOGIN_FAILED:
	  outingString = "Server output: LOGIN_FAILED( " + QString(type) + ") DATE: " + dateString + " TIME: " + timeString + "+empty{}\n";
	  qDebug() << outingString << "\n";
      break;
    case (quint8)ServerRequests::REGISTER_FAILED:
	  outingString = "Server output: REGISTER_FAILED( " + QString(type) + ") DATE: " + dateString + " TIME: " + timeString + "+empty{}\n";
	  qDebug() << outingString << "\n";
	  WriteLogToFile(QString("LOG.txt"), outingString);
      break;
    case (quint8)ServerRequests::FRIEND_REQUEST_FAILED:
	  outingString = "Server output: FRIEND_REQUEST_FAILED( " + QString(type) + ") DATE: " + dateString + " TIME: " + timeString + "+empty{}\n";
	  qDebug() << outingString << "\n";
	  WriteLogToFile(QString("LOG.txt"), outingString);
      break;
    case (quint8)ServerRequests::FRIEND_REQUEST_SUCCEED: {
	  outingString = "Server output: FRIEND_REQUEST_SUCCEED( " + QString(type) + ") DATE: " + dateString + " TIME: " + timeString + "+empty{}\n";
	  qDebug() << outingString << "\n";
	  WriteLogToFile(QString("LOG.txt"), outingString);
      break;
    }
    case (quint8)ServerRequests::REGISTER_SUCCEED: {
      RegisterSuccessInfo out;
      out = Parser::ParseAsRegisterSuccessInfo(raw_data);
      outingString= "Server  output: REGISTER_SUCCEED(" + QString(type) + 
		")+RegisterSuccessInfo{ " + QString(out.id) + " }" +
		" DATE: " + dateString + " TIME: " + timeString + "\n";

	  qDebug() << outingString << "\n";
	  WriteLogToFile(QString("LOG.txt"), outingString);
      break;
    }
    case (quint8)ServerRequests::ADD_FRIEND_REQUEST: {
      AddFriendInfo out;
      out = Parser::ParseAsAddFriendInfo(raw_data);
      outingString = "Server  output: ADD_FRIEND_REQUEST(" + QString(type) +
               + ")+AddFriendInfo{ " + out.requester_ip.toString() + ", "
               + out.requester_login +", " + QString(out.requester_port) + " }"+
		      " DATE: " + dateString + " TIME: " + timeString + "\n";

	  qDebug() << outingString << "\n";
	  WriteLogToFile(QString("LOG.txt"),outingString);
      break;
    }
    case (quint8)ServerRequests::FRIEND_UPDATE_INFO: {
      FriendUpdateInfo out;
      out = Parser::ParseAsFriendUpdateInfo(raw_data);
	  outingString =  "Server  output: FRIEND_UPDATE_INFO(" + QString(type)+
                ") + RegisterSuccessInfo{ " + QString(out.id) + ", " + out.ip.toString() + ", "+ QString(out.port) +" }" +
		" DATE: " + dateString + " TIME: " + timeString + "\n";
	  qDebug() << outingString << "\n";
	  WriteLogToFile(QString("LOG.txt"), outingString);
      break;
    }
  }
}
