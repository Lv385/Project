#ifndef MESSAGE_H
#define MESSAGE_H
#include <QDate>
#include <QString>
#include <QTime>
#include <qvector.h>
#include<qsqlrecord.h>
#include "clientdal.h"

class Message : public ClientDAL{
 public:
	 Message(const QString &connection_name);
	 Message();


  unsigned int id;
  unsigned int chat_id;
  unsigned int owner_id;
  QString data;
  QDate date;
  QTime time;
  bool status;


  QVector<Message> GetMessages();//SelectAllInfoAboutOneChat
  void UpdateMessage();//Update
  void AddNewMessage();//Insert
  void DeleteMessage();//Delete

//private:

  QString CreateQuerySelectAll();
  QString CreateQueryInsert();
  QString CreateQueryUpdate();
  QString CreateQueryDelete();
  QString CreateQueryCountOfMessages();


};

#endif  // MESSAGE_H#pragma once
