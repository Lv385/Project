#ifndef APPLICATIONINFO_H
#define APPLICATIONINFO_H

#include <QHostAddress>
#include <QString>
#include <QSet>

struct ApplicationInfo {
  QHostAddress remote_server_ip;
  quint16 remote_server_port;

  QHostAddress my_ip;
  quint16 my_port;

  quint32 my_id;
  QString my_login;
  QString my_password;
};

#endif  // !APPLICATIONINFO_H
