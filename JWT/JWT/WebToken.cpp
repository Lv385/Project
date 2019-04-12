#include "WebToken.h"

// void WebToken::GenerateToken() {   }

//WebToken::WebToken(): payload(nullptr),signature(nullptr) {
//  header["alg"] = "SPECK";
//  header["typ"] = "JWT";
//}

void WebToken::GenerateToken(const std::string& key) {
  token_ = base64_encode((const unsigned char*)header.dump().c_str(),
                         header.dump().length());
  token_ += '.';
  token_ += base64_encode((const unsigned char*)payload.dump().c_str(),
                          payload.dump().length());
  signature = 

}

void WebToken::SetPayload(const unsigned int id) { payload["id"] = id; }

void WebToken::SetHeader(const std::string& algorithm_name,
                         const std::string& type) {
    header["alg"] = algorithm_name;
    header["typ"] = type;
}

