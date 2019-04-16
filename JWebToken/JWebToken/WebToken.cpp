#include "WebToken.h"

WebToken::WebToken(const std::string& token) : token_(token) {}

std::string WebToken::GetToken(const std::string& key) {  // TODO
  token_ = base64_encode((const unsigned char*)header_.dump().c_str(),
                         header_.dump().length());
  token_ += '.';
  token_ += base64_encode((const unsigned char*)payload_.dump().c_str(),
                          payload_.dump().length());
  QByteArray result = QByteArray::fromStdString(token_);

  cypher.Encrypt(result, QString::fromStdString(key));

  signature_ = result.toStdString();
  token_ += '.';
  token_ += signature_;
  return token_;
}

void WebToken::SetPayload(const unsigned int id) { payload_["id"] = id; }

void WebToken::SetHeader(const std ::string& algorithm_name,
                         const std ::string& type) {
  header_["alg"] = algorithm_name;
  header_["typ"] = type;
}

void WebToken::ParseToken() {
  //-------------Finding position of first dot----------------------
  auto f_dot = token_.find_first_of('.');

  std::string::iterator front = token_.begin() + f_dot;

  //-----Decoding of string from begin till first dot position-------
  auto header = base64_decode(std::string(token_.begin(), front - 1));
  header_ = json::parse(header);
  
  //-------------Finding position of second dot----------------------
  auto s_dot = std::string(++front, token_.end()).find_first_of('.');
  std::string::iterator last_dot = token_.begin() + f_dot + s_dot + 1;

  //-----Decoding of string from first dot till second dot-------
  auto payload =
      base64_decode(std::string(front, last_dot));
  payload_ = json::parse(payload);

  //-----Set signature of our sended token----------------------
  last_dot++;
  signature_ = std::string(last_dot, token_.end());
}

bool WebToken::IsSignatureValid(const std::string& key) { 
  QByteArray result = QByteArray::fromStdString(signature_);

  std::string signature{};

  cypher.Decrypt(result,QString::fromStdString(key));
  signature = result.toStdString();
  auto position_of_null = signature.find_first_of('\0');

  //This because decoding is incorrect =(
  std::string::iterator null_iterator = signature.begin() + position_of_null;
  signature = std::string(signature.begin(), null_iterator);

  std::string to_compare{};
  to_compare += base64_encode((const unsigned char*)header_.dump().c_str(),
                              header_.dump().length());
  to_compare += ".";
  to_compare += base64_encode((const unsigned char*)payload_.dump().c_str(),
                              payload_.dump().length());
  
  return to_compare == signature;
}
