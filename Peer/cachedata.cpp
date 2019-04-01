#include "cachedata.h"

CacheData::CacheData() {}

CacheData& CacheData::get_instance() {
  static CacheData instance_;
  return instance_;
}

QString CacheData::GetMessage(unsigned id) { 
  return messages_[id]; 
}

void CacheData::SetMessage(unsigned id, QString message) {}
