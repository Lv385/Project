#pragma once

#include <QObject>
#include <QHash>
class CacheData : public QObject
{
  Q_OBJECT

public:
  static CacheData& get_instance();
  CacheData(CacheData const&) = delete;
  void operator=(CacheData const&) = delete;
  QString GetMessage(unsigned id);
  void SetMessage(unsigned id, QString message);

  private:
  CacheData();
  QHash<int, QString> messages_;
};
