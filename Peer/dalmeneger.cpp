#include "dalmeneger.h"
DALMeneger::DALMeneger()  {

}

DALMeneger::~DALMeneger()
{}

void DALMeneger::AddMessageToDB(QString message, unsigned user_id, unsigned owner_id) {
  ClientDAL::ClientDB cdb;
  ClientDAL::Message msg;
  msg.data = message;
  msg.owner_id = owner_id;
  msg.date = QDate::currentDate();
  msg.time = QTime::currentTime();
  cdb.AddMessage(msg, user_id);
}

void DALMeneger::UpdateIpPort(unsigned id, QString new_ip, unsigned new_port) {
  ClientDAL::ClientDB cdb;
  cdb.UpdateIPPort(id, new_ip, new_port);
}
