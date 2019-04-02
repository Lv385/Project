#ifndef CLIENT_DATA_TYPES_H
#define CLIENT_DATA_TYPES_H

#include <QString>
#include <QDate>
#include <QTime>
//
//// This is our entity from database
struct Friend {
  unsigned int id;
  QString ip;
  unsigned int port;
  QString login;
  QString name;
  QString surname;
  bool status;
  // IMAGE photo  //in progress
};
//
struct Message {
  unsigned int id;
  unsigned int chat_id;
  unsigned int owner_id;
  QString data;
  QDate date;
  QTime time;
  bool status;
};
//
#endif  // !1CLIENT_DATA_TYPES_H
