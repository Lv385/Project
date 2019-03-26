#ifndef FRIENDSWORKER_H
#define FRIENDSWORKER_H

#include <QObject>

class FriendsWorker : public QObject {
  Q_OBJECT

 public:
  FriendsWorker(QObject *parent);
  ~FriendsWorker();
};
#endif  // !FRIENDSWORKER_H
