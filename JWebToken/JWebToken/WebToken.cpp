#include "WebToken.h"

// void WebToken::GenerateToken() {   }

//WebToken::WebToken(): payload(nullptr),signature(nullptr) {
//  header["alg"] = "SPECK";
//  header["typ"] = "JWT";
//}

void WebToken::GenerateToken(const QString& key) { //TODO 
  token_ = QString::fromStdString(base64_encode((const unsigned char*)header.dump().c_str(),
                         header.dump().length()));
  token_ += '.';
  token_ +=QString::fromStdString(base64_encode((const unsigned char*)payload.dump().c_str(),
                          payload.dump().length()));
  QByteArray result;
  QDataStream out(&result, QIODevice::ReadWrite);
  out << token_;
  cypher.Encrypt(result, key);
 // cypher.Decrypt(result, key);

  signature = QString::QString(result);
  token_ += signature;
}

void WebToken::SetPayload(const unsigned int id) { payload["id"] = id; }

void WebToken::SetHeader(const QString& algorithm_name, const QString& type) {
    header["alg"] = algorithm_name.toStdString();
	header["typ"] = type.toStdString();
}

