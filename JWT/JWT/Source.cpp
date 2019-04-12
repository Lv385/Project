#include <iostream>
#include <string>
#include "WebToken.h"


using json = nlohmann::json;

int main() {
  WebToken access;
  access.SetPayload(4);
  access.SetHeader("SPEK");
  access.GenerateToken();
  std::cout << access.token_;
  //json s = nullptr;
  //std::string sstr = nullptr;
  system("pause");
  return 0;
}