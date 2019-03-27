#ifndef APPLICATIONINFO_H
#define APPLICATIONINFO_H

#include <QHostAddress>
#include <QString>
#include <QSet>

struct ApplicationInfo {
  QHostAddress remote_server_ip;
  quint16 remote_server_port;

  QHostAddress app_server_ip;
  quint16 app_server_port;
};

#endif  // !APPLICATIONINFO_H
