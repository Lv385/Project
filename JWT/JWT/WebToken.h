#ifndef WEB_TOKEN
#define WEB_TOKEN

#include <string>
#include <windows.data.json.h>
#include "../json/single_include/nlohmann/json.hpp"
#include "base64.h"

using json = nlohmann::json;

class WebToken {
 public:
  std::string token_;
  json header;
  json payload;
  std::string signature;
  explicit WebToken() = default;
  virtual~WebToken() = default;
  void GenerateToken(const std::string& key);
  void SetPayload(const unsigned int id);
  void SetHeader(const std::string& algorithm_name, const std::string& type = "JWT");
};


#endif  // !WEB_TOKEN

