#ifndef MESSAGE_H
#define MESSAGE_H
#include <QDate>
#include <QString>
#include <QTime>

struct Message {
 public:
  unsigned int id;
  unsigned int chat_id;
  unsigned int owner_id;
  QString data;
  QDate date;
  QTime time;
  bool status;
};

#endif  // MESSAGE_H#pragma once
