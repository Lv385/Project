#ifndef FRIEND_H
#define FRIEND_H
#include <QString>

struct Friend {
 public:
  unsigned int id;
  QString ip;
  unsigned int port;
  QString login;
  QString name;
  QString surname;
  bool status;
};

#endif  // FRIEND_H