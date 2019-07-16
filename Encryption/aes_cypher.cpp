#include "aes_cypher.h"
//Aes 256 CBS block cyphering  //  actually aes128 CBC ISO padding

AESCypher::AESCypher()
{
  //aes 128
  number_of_blocks_ = 4; // possibly blocksnum // check it
  blocklength_ = 16;
  number_of_keys_ = 4;
  keylen_ = 16;
  rounds_num_ = 10; // rounds number for aes256 is 14
  expanded_key_ = 176;
  padding_; //ISO
}
void AESCypher::CharSwap(char &a, char &b)
{
  char tmp = a;
  a = b;
  b = tmp;

}
void AESCypher::swap(quint8 a, quint8 b)
{
  quint8 tmp = a;
  a = b;
  b = tmp;
}
void AESCypher::Encrypt(QByteArray& plaintext, QString key)
{
  iter_state = &plaintext;
  QByteArray b_key = ConvertStringToByteArr(key);
  XorRoundKey(plaintext,b_key,0);
  for (quint8 round = 1; round < rounds_num_; ++round) {
    SubBytes(plaintext);
    ShiftRows();
    MixColumns();
    XorRoundKey(plaintext,b_key,round); 
  }
  //last round
  SubBytes(plaintext);
  ShiftRows();
  XorRoundKey(plaintext, b_key,rounds_num_);
}
void AESCypher::Decrypt(QByteArray & plaintext, QString key)
{
  QByteArray b_key = ConvertStringToByteArr(key);
  XorRoundKey(plaintext, b_key, rounds_num_);
  for (quint8 round = rounds_num_ - 1; round > 0; round--) {
    InvShiftRows();
    InvSubBytes();
    XorRoundKey(plaintext,ConvertStringToByteArr(key), round);
    InvMixColumns();
    
  }
  InvShiftRows();
  InvSubBytes();
  XorRoundKey(plaintext, b_key, 0);
}
// multipliying x on {02}  by polynom 0x1b    {}-hexadecimal notation
inline quint8 AESCypher::xTime(quint8 x)
{
  return ((x << 1) ^ (((x >> 7) & 1) * 0x1b));
}
inline quint8 AESCypher::Multiply(quint8 x, quint8 y)
{
  return (((y & 1) * x) ^ ((y >> 1 & 1) * xTime(x)) ^ ((y >> 2 & 1) * xTime(xTime(x))) ^ ((y >> 3 & 1)
    * xTime(xTime(xTime(x)))) ^ ((y >> 4 & 1) * xTime(xTime(xTime(xTime(x))))));
}
// done
void AESCypher::SubBytes(QByteArray& text)
{ 
  // substituting data by values from SBox
  QByteArray::iterator it = iter_state->begin();
  for (int i = 0; i < 16; i++)
    text[i] = GetSBoxValue((quint8)it[i]);
}
//done
void AESCypher::InvSubBytes()
{
  QByteArray::iterator it = iter_state->begin();
  for (int i = 0; i < 16; i++)
    it[i] = GetSBoxInvert((quint8)it[i]); // get data from rsbox
}
//done
void AESCypher::ShiftRows()
{
  QByteArray::iterator it = iter_state->begin();
  swap((quint8)it[0] , (quint8)it[0]);
  swap((quint8)it[1], (quint8)it[13]);
  swap((quint8)it[2], (quint8)it[10]);
  swap((quint8)it[3], (quint8)it[7]);
  
  swap((quint8)it[4], (quint8)it[4]);
  swap((quint8)it[5], (quint8)it[1]);
  swap((quint8)it[6], (quint8)it[14]);
  swap((quint8)it[7], (quint8)it[11]);

  swap((quint8)it[8], (quint8)it[8]);
  swap((quint8)it[9], (quint8)it[5]);
  swap((quint8)it[10], (quint8)it[2]);
  swap((quint8)it[11], (quint8)it[15]);

  swap((quint8)it[12], (quint8)it[12]);
  swap((quint8)it[9], (quint8)it[13]);
  swap((quint8)it[14], (quint8)it[6]);
  swap((quint8)it[15], (quint8)it[3]);
}
//done
void AESCypher::InvShiftRows()
{
  QByteArray::iterator it = iter_state->begin();
  swap((quint8)it[1], (quint8)it[5]);
  swap((quint8)it[1], (quint8)it[9]);
  swap((quint8)it[7], (quint8)it[11]);
  swap((quint8)it[7], (quint8)it[15]);
  
}
//done
void AESCypher::MixColumns()
{
 // + is XOR     * is bitwise AND
   //  00011011 is representing  pow(x,8)+ pow(x,4) +pow(x,3) + pow(x,1)+1 // pow(x,n) == x*x*x*x*... n times
 // possibly working
  QByteArray::iterator it = iter_state->begin();
  quint8 tmp, tm, t;
  
  for (int i = 0; i < 16; i += 4) 
  {
    quint8 t = (quint8)it[i] ^ (quint8)it[i+1] ^ (quint8)it[i+2] ^ (quint8)it[i+3];
    quint8 u = (quint8)it[i];
    it[i] =  (quint8)it[i] ^ (quint8)xTime(it[i] ^ it[i + 1]) ^ (quint8)t;
    it[i+1]= (quint8)it[i+1] ^ (quint8)xTime(it[i+1] ^ (quint8)it[i + 2]) ^ (quint8)t;
    it[i+2]= (quint8)it[i+2] ^ (quint8)xTime(it[i+2] ^ (quint8)it[i + 3]) ^ (quint8)t;
    it[i+3]= (quint8)it[i+3] ^ (quint8)xTime(it[i+3] ^ u) ^ (quint8)t;
  }
  
}
//done
void AESCypher::InvMixColumns()
{
  QByteArray::iterator it = iter_state->begin();
  quint8 a, b, c, d;
  for (int i = 0; i < 16; i += 4) {
    a = (quint8)it[i];
    b = (quint8)it[i + 1];
    c = (quint8)it[i + 2];
    d = (quint8)it[i + 3];

    it[i] = (quint8)(Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^ Multiply(d, 0x09));
    it[i + 1] = (quint8)(Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^ Multiply(d, 0x0d));
    it[i + 2] = (quint8)(Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^ Multiply(d, 0x0b));
    it[i + 3] = (quint8)(Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^ Multiply(d, 0x0e));
  }

}

void AESCypher::XorRoundKey(QByteArray&plaintext,QByteArray&key,quint8 round)
{
  quint8 nb = 4;
  QByteArray::iterator it = iter_state->begin();
  /*for (int i = 0; i < 16; ++i)
    it[i] = (quint8)it[i] ^ (quint8)key.at(round * nb * 4 + (i / 4) * nb + (i % 4));*/
  for (int i = 0; i < 16; ++i)
    it[i] = (quint8)it[i] ^ (quint8)key[i];
}


int AESCypher::gcd(int a, int b) {
  int t;
  while (b != 0) {
    t = b;
    b = a % b;
    a = t;
  }
  return a;
}



