#include "abstract_cypher.h"
#define ROUNDS_NUMBER 27
// size of word is 32 bit (1 word)
// size of block 2*32 = 64 bit (2 word)
// size of key  4*32 = 128 bit (4 word)

class SpeckCypher : AbstractCypher {
  /* Example of usage with std::string as plaint text and key. 
        ________________________________________________________________________________
        SpeckCypher speck;
        std::string plain_text( "Hello encryption aaaaaaaaaaaaaaaa :)))))"); 
        std::string key("ab301234aiEr12d4");                   // 128bits
        QByteArray text(plain_text.c_str());
        QString keyQ = QString::fromUtf8(key.c_str());
        std::cout << text.toStdString() << std::endl;
        speck.Encrypt(text, keyQ);
        std::cout << text.toStdString() << std::endl;
        speck.Decrypt(text, keyQ);
        std::cout << text.toStdString() << std::endl;
        ________________________________________________________________________________
  */
 public:
  void Encrypt(QByteArray& plain_text, QString key);
  void Decrypt(QByteArray& cypher_text, QString key);

 private:
  const int ROUNDS = ROUNDS_NUMBER;
  const int WORD_STRIDE = 4;
  const int WORD_SIZE_BITS = 32;
  uint32_t key_schedule[ROUNDS_NUMBER];
  void SpeckRound(uint32_t& x, uint32_t& y, uint32_t k);
  void SpeckBack(uint32_t& x, uint32_t& y, uint32_t k);
  void CreateKeys(const uint32_t key[4]);
  void EncryptBlock(const uint32_t plaintext[2], uint32_t ciphertext[2]);
  void DecryptBlock(const uint32_t ciphertext[2], uint32_t decrypted[2]);
  uint32_t GetWord(char const* str, unsigned int word_index);   
  char* BinaryToWord(uint32_t word);
};