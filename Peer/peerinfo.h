#ifndef PEERINFO_H
#define PEERINFO_H

#include <QHostAddress>
#include <QString>
#include <memory>

struct PeerInfo {
  quint32 id;
  QString login;
  QHostAddress ip;
  quint16 port;
  bool is_online;
};

#endif  // !PEERINFO_H
