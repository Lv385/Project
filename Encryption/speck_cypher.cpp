#include "speck_cypher.h"

//Key must be 128 bit string (16 chars). Same key is used for encryption
//and for decryption. Example of a valid keys: "0123456701234567",
//"abcdefghabcdefgh"
void SpeckCypher::Encrypt(QByteArray& plain_text, QString key) {  
  // in order to encryption to work size of an array should be factor of 8. Enforcing it here
  int newSize = plain_text.size();
  if (newSize % 8 != 0) {
    plain_text.resize(8 - newSize % 8 + newSize);
  }
  // extract data to encrypt
  char* plain_text_ptr = plain_text.data();  
  // cast key to simple char
  char const* k = key.toStdString().c_str();
  // divide key into words 4 words (32x4)
  uint32_t key_arr[] = {GetWord(k, 0), GetWord(k, 1), GetWord(k, 2),
                        GetWord(k, 3)};
  // get keys for each round of encryption 
  CreateKeys(key_arr);
  // prepare for encryption:
  // create temporary cypher text block
  uint32_t ct_temp_block[2];
  // numbers of block  to encrypt
  int blocks_count = plain_text.size() / 8;
  // encryption cycle
  for (int i = 0; i < blocks_count; i++) {
    //get two consecutive words (one block) from plain text at each iteration
    uint32_t plain_text_block[] = {GetWord(plain_text_ptr, i * 2),
                                 GetWord(plain_text_ptr, i * 2 + 1)};
    // encrypt that block
    EncryptBlock(plain_text_block, ct_temp_block);
    
    char* firstWord = BinaryToWord(ct_temp_block[0]);
    //TODO:: change this to memcpy!!!!
    for (int j = 0; j < 4; j++) {
      //modify original plain text
      plain_text_ptr[i * 8 + j] = firstWord[j];
    }
    char* secondWord = BinaryToWord(ct_temp_block[1]);
    // TODO:: change this to memcpy!!!!
    for (int j = 0; j < 4; j++) {
      // modify original plain text
      plain_text_ptr[i * 8 + 4 + j] = secondWord[j];
    }
  }  
}

void SpeckCypher::Decrypt(QByteArray& cypher_text, QString key) {  
  char* cypher_text_ptr = cypher_text.data();  
  char const* k = key.toStdString().c_str();  
  uint32_t key_arr[] = {GetWord(k, 0), GetWord(k, 1), GetWord(k, 2),
                        GetWord(k, 3)};  
  CreateKeys(key_arr);
  uint32_t pt_temp_block[2];  
  int blocks_count = cypher_text.size() / 8;
  for (int i = 0; i < blocks_count; i++) {
    uint32_t cypher_text_block[] = {GetWord(cypher_text_ptr, i * 2),
                                    GetWord(cypher_text_ptr, i * 2 + 1)};
    DecryptBlock(cypher_text_block, pt_temp_block);
    char* firstWord = BinaryToWord(pt_temp_block[0]);
    for (int j = 0; j < 4; j++) {
      cypher_text_ptr[i * 8 + j] = firstWord[j];
    }
    char* secondWord = BinaryToWord(pt_temp_block[1]);
    for (int j = 0; j < 4; j++) {
      cypher_text_ptr[i * 8 + 4 + j] = secondWord[j];
    }
  }
  
}
// One encryption round.
void SpeckCypher::SpeckRound(uint32_t& x, uint32_t& y, uint32_t k) {
  // rotate right: 1000 0000 0001 become 0000 0000 1100
  x = (x >> 8) | (x << (8 * sizeof(x) - 8));
  // add two words
  x += y;
  // XOR it with key
  x ^= k;
  // rotate left: 1000 0000 0001 become 0000 0000 1100
  y = (y << 3) | (y >> (8 * sizeof(y) - 3));  
  // XOR second word with other
  y ^= x;
}
// Perform all the task that a function above but in reverse order
void SpeckCypher::SpeckBack(uint32_t& x, uint32_t& y, uint32_t k) {
  y ^= x;
  y = (y >> 3) | (y << (8 * sizeof(y) - 3));
  x ^= k;
  x -= y;
  x = (x << 8) | (x >> (8 * sizeof(x) - 8));
}
// Create keys used for each round
void SpeckCypher::CreateKeys(const uint32_t key[4]) {
  uint32_t b = key[0];
  uint32_t a[3];
  a[0] = key[1];
  a[1] = key[2];
  a[2] = key[3];
  key_schedule[0] = b;
  for (unsigned i = 0; i < ROUNDS - 1; i++) {
    SpeckRound(a[i % 3], b, i + 1);
    key_schedule[i + 1] = b;
  }
}

void SpeckCypher::EncryptBlock(const uint32_t plaintext[2],
                               uint32_t ciphertext[2]) {
  ciphertext[0] = plaintext[0];
  ciphertext[1] = plaintext[1];
  for (unsigned i = 0; i < ROUNDS; i++) {
    SpeckRound(ciphertext[1], ciphertext[0], key_schedule[i]);
  }
}

void SpeckCypher::DecryptBlock(const uint32_t ciphertext[2],
                               uint32_t decrypted[2]) {
  decrypted[0] = ciphertext[0];
  decrypted[1] = ciphertext[1];
  for (unsigned i = ROUNDS; i > 0; i--) {
    SpeckBack(decrypted[1], decrypted[0], key_schedule[i - 1]);
  }
}

// returns 32 bit word 
uint32_t SpeckCypher::GetWord(char const* str, unsigned int word_index) {
  return ((uint8_t)str[(WORD_STRIDE * word_index) + 0] << 24) |
         ((uint8_t)str[(WORD_STRIDE * word_index) + 1] << 16) |
         ((uint8_t)str[(WORD_STRIDE * word_index) + 2] << 8) |
         ((uint8_t)str[(WORD_STRIDE * word_index) + 3]);
}

// Get chars out of int crunched on ecryption stage  
char* SpeckCypher::BinaryToWord(uint32_t word) {
  static char to_ret[4];
  // 1111 1111 0000 0000 0000 0000 0000 0000 in binary form
  uint32_t mask = 4278190080;
  for (int i = 0; i < 4; i++) {
    to_ret[i] = (char)((word & mask) >> (3 - i) * 8);
    mask = mask >> 8;
  }
  return to_ret;
}
