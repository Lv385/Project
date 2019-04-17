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
void AESCypher::swap(char &a, char &b)
{
  char tmp = a;
  a = b;
  b = tmp;

}
void AESCypher::Encrypt(QByteArray& plaintext, QString key)
{
  AESCypher();
  iter_state = &plaintext;
  QVector<char>C_s;
  //addRoundKey(0, expKey);
  qDebug() << "    " << plaintext << "\n";
  for (quint8 round = 1; round < rounds_num_; ++round) {
    SubBytes(plaintext);
    ShiftRows(plaintext);
    MixColumns(plaintext,C_s);
    //addRoundKey(round, expKey);
  }
  qDebug() << "  encrypted: " << plaintext << "\n";
  
  for (quint8 round = 1; round < rounds_num_; ++round) {
    InvShiftRows(plaintext);
    InvSubBytes(plaintext);
    InvMixColumns(plaintext,C_s);
     //addRoundKey(round, expKey);
  }
  qDebug() << "  decrypted: " << plaintext << "\n";
  //SubBytes();
  //ShiftRows();
  //addRoundKey(rounds_num_, expKey);
  qDebug() << "" << ConvertByteArrayToString( plaintext)<<"\n";
}
void AESCypher::Decrypt(QByteArray & plaintext, QString key)
{
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
void AESCypher::ShiftRows(QByteArray& text)
{
  QByteArray::iterator it = iter_state->begin();
  swap(it[0] , it[0]); 
  swap(it[1], it[13]);
  swap(it[2], it[10]);
  swap(it[3], it[7]);
  
  swap(it[4], it[4]);
  swap(it[5], it[1]);
  swap(it[6],it[14]);
  swap(it[7],it[11]);

  swap(it[8],it[8]);
  swap(it[9],it[5]);
  swap(it[10],it[2]);
  swap(it[11],it[15]);

  swap(it[12],it[12]);
  swap(it[9],it[13]);
  swap(it[14],it[6]);
  swap(it[15],it[3]);
  
  
}
//done
void AESCypher::InvShiftRows(QByteArray)
{
  QByteArray::iterator it = iter_state->begin();
  swap(it[1], it[5]);
  swap(it[1],it[9]);
  swap(it[7], it[11]);
  swap(it[7],it[15]);
}
void AESCypher::MixColumns(QByteArray& plaintext, QVector<char>&C_s)
{
  // a(x) polynomial of 4 power 
  //res == a(x)*c(x)
  //every column
  //a(x) =  x*x*x*x + x*x*x + x*x + x +1
  //c(x) = 3*x*x*x + x*x + x+2
 // + is XOR     * is bitwise AND
   //  00011011 is representing  pow(x,8)+ pow(x,4) +pow(x,3) + pow(x,1)+1  pow(x,n) == x*x*x*x*... n times
 // possibly working

  QByteArray::iterator it = iter_state->begin();
 
  for (int i = 0; i < 16; i++)
  {
    char a_x= (it[i] & it[i] & it[i] & it[i]) ^ (it[i] & it[i] & it[i]) ^ (it[i] & it[i]) ^ 1;
    char c_x = (3 & it[i] & it[i] & it[i]) ^ (it[i] & it[i]) ^ (it[i])^2;
      it[i] = a_x & c_x;
      C_s.push_back(c_x);
  }
}

void AESCypher::XorRoundKey(QByteArray)
{
}
//done
void AESCypher::InvSubBytes(QByteArray) 
{
  QByteArray::iterator it = iter_state->begin();
  for (int i = 0; i < 16; i++)
    it[i] = GetSBoxInvert((quint8)it[i]); // get data from rsbox
}


void AESCypher::InvMixColumns(QByteArray & plaintext,QVector<char>&C_S)
{
  //sraka povna
  // a(x)=res/c(x)
  QByteArray::iterator it = iter_state->begin();
  for (int i = 0; i < 16; i++)
  {
    it[i]=(char)gcd(it[i],C_S[i]);
  }

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



