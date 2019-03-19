#include "message.h"

Message::Message(std::shared_ptr<Connection> connection)
    : Statement(connection) {
  connection_->Open(CLIENT_DB);
  id = 0;
  data = "";
  owner_id = 0;
  date = QDate::currentDate();
  time = QTime::currentTime();
  status = false;
}

Message::Message() : Statement() {}

QVector<Message> Message::GetMessages() {
  ExectuteQuery(CreateQueryCountOfMessages());
  query_.first();
  unsigned int CountOfMessages = query_.value(0).toInt();
  QVector<Message> result(CountOfMessages);
  ExectuteQuery(SelectQuery());
  int counter = 0;
  while (query_.next()) {
    result[counter].id = query_.record().value(0).toInt();
    result[counter].chat_id = query_.record().value(1).toInt();
    result[counter].owner_id = query_.record().value(2).toInt();
    result[counter].data = query_.record().value(3).toString();
    result[counter].date = query_.record().value(4).toDate();
    result[counter].time = query_.record().value(5).toTime();
    result[counter++].status = query_.record().value(6).toInt();
  }
  return result;
}

void Message::AddNewMessage() {
  ExectuteQuery(InsertQuery());
  query_.finish();
}

void Message::DeleteMessage() {
  ExectuteQuery(DeleteQuery());
  query_.finish();
}

void Message::UpdateMessage() {
  ExectuteQuery(UpdateQuery());
  query_.finish();
}

QString Message::SelectQuery() {
  return QString("select * from Messages where user_ID = " +
                 QString::number(chat_id));
}

QString Message::InsertQuery() {
  return QString(
      "insert into Messages (user_ID, owner_ID, message_data, message_date, "
      "message_tima, message_status) values (" +
      QString::number(chat_id) + ", " + QString::number(owner_id) + ", '" +
      data + "', '" + date.toString() + "', '" + time.toString() + "', " +
      QString::number(status) + ")");
}

QString Message::UpdateQuery() {
  return QString("update Messages set message_data = '" + data +
                 "', message_status = '" + QString::number(status) +
                 "'  where message_ID = " + QString::number(id));
}

QString Message::DeleteQuery() {
  return QString("delete from Messages where message_ID = " +
                 QString::number(id));
}

QString Message::CreateQueryCountOfMessages() {
  return QString("SELECT COUNT(user_ID) FROM Messages WHERE user_ID = " +
                 QString::number(chat_id));
}
