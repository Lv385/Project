#include "WebToken.h"

std::string WebToken::GetToken(const std::string& key) {  // TODO
  token_ = base64_encode(
      (const unsigned char*)header_.dump().c_str(), header_.dump().length());
  token_ += '.';
  token_ += base64_encode(
      (const unsigned char*)payload_.dump().c_str(), payload_.dump().length());
  token_ += '.';
  QByteArray result = QByteArray::fromStdString(token_);

  cypher.Encrypt(result, QString::fromStdString(key));

  signature_ = result.toStdString();
  token_ += signature_;
  return token_;
}

void WebToken::SetPayload(const unsigned int id) { payload_["id"] = id; }

void WebToken::SetHeader(const std ::string& algorithm_name,
                         const std ::string& type) {
  header_["alg"] = algorithm_name;
  header_["typ"] = type;
}
