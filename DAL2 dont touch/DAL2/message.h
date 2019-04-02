#ifndef MESSAGE_H
#define MESSAGE_H

#include <qsqlrecord.h>
#include <qvector.h>
#include <QDate>
#include <QString>
#include <QTime>
#include "statement.h"

namespace SQLDAL {

struct Message {
  unsigned int id;
  unsigned int chat_id;
  unsigned int owner_id;
  QString data;
  QDate date;
  QTime time;
  bool status;
};

class Messages : public Statement {
 public:
  Messages(std::shared_ptr<Connect> Connect);
  Messages();

  QVector<Message> GetMessages(
      unsigned int chat_id);  // Select All Info About One Chat
  QVector<Message> GetMessages(
      QString user_login);  // Select All Info About One Chat
  void AddNewMessage(const Message& message);
  void DeleteMessage(const Message& message);
  void UpdateMessage(const Message& message);

 private:
  QString UpdateQuery(const Message& message);
  QString SelectQuery(unsigned int chat_id);
  QString SelectQuery(QString user_login);
  QString InsertQuery(const Message& message);
  QString DeleteQuery(const Message& message);
  QString CreateQueryCountOfMessages(unsigned int chat_id);
  QString CreateQueryCountOfMessages(QString user_login);
};
}  // namespace SQLDAL
#endif  // MESSAGE_H
