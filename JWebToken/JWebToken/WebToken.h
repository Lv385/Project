#ifndef WEB_TOKEN
#define WEB_TOKEN

#include <windows.data.json.h>
#include <QDataStream>
#include <string>
#include "../Encryption/speck_cypher.h"
#include "base64.h"
#include "json\single_include\nlohmann\json.hpp"

using json = nlohmann::json;

class WebToken {
 public:
  QString token_;
  json header;
  json payload;
  QString signature;
  SpeckCypher cypher;
  explicit WebToken() = default;
  virtual ~WebToken() = default;
  void GenerateToken(const QString& key);
  void SetPayload(const unsigned int id);
  void SetHeader(const QString& algorithm_name, const QString& type = "JWT");
};

#endif  // !WEB_TOKEN
