#ifndef DALLMENEGER_H
#define DALLMENEGER_H

#include "../DAL/Client/clientdb.h"
#include "../Parser&Structs/request_types.h"

class DALMeneger {
 public:
  DALMeneger();
  ~DALMeneger();

  void AddMessageToDB(QString message, unsigned user_id, unsigned owner_id);
  void UpdateIpPort(unsigned id, QString new_ip, unsigned new_port);

 private:
  
};
#endif
