#include "aes_cypher.h"
//Aes 256 CBS block cyphering  //  actually aes128

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
void AESCypher::swap(int &a, int &b)
{
  int tmp = a;
  a = b;
  b = tmp;

}
void AESCypher::Encrypt(QByteArray& plaintext, QByteArray&key)
{
  AESCypher();

  iter_state = &plaintext;
  //addRoundKey(0, expKey);
  SubBytes(plaintext);
  qDebug() << "    " << plaintext << "\n";
  ShiftRows(plaintext);
  qDebug() << "  Shifted rows:" << plaintext << "\n";
  InvShiftRows(plaintext);//problem
  qDebug() << "  Inv Shifted Rows: " << plaintext << "\n";
  InvSubBytes(plaintext);
 
  //ShiftRows(QByteArray);
  //MixColumns(QByteArray);

  //for (quint8 round = 1; round < rounds_num_; ++round) {
  //  SubBytes();
  //  ShiftRows();
  //  MixColumns();
  //  //addRoundKey(round, expKey);
  //}
  //SubBytes();
  //ShiftRows();
  //addRoundKey(rounds_num_, expKey);

}
// done
void AESCypher::SubBytes(QByteArray&Text)
{ 
  // substituting data by values from SBox
  QByteArray::iterator it = iter_state->begin();
  for (int i = 0; i < 16; i++)
    Text[i] = GetSBoxValue((quint8)it[i]);
}

void AESCypher::ShiftRows(QByteArray)
{
  // here we swap rows in only us known order
  QByteArray::iterator it = iter_state->begin();
 // int it[16]{ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
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
  /*for(int i=0;i<16;i++)
  {
    qDebug() << it[i]<<" "<< i<<" ";
  }*/
  
}
void AESCypher::InvShiftRows(QByteArray)
{
  
  QByteArray::iterator it = iter_state->begin();
  //int it[16]{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
  //int it[16] = {0,5,2,3,4,9,6,11,8,1,10,15,12,13,14,7};
  
  swap(it[1], it[5]);
  swap(it[1],it[9]);
  swap(it[7], it[11]);
  swap(it[7],it[15]);
  /*swap(it[0], it[0]);
  swap(it[13], it[1]);
  swap(it[10], it[2]);
  swap(it[7], it[3]);

  swap(it[4], it[4]);
  swap(it[1], it[5]);
  swap(it[14], it[6]);
  swap(it[11], it[7]);

  swap(it[8], it[8]);
  swap(it[5], it[9]);
  swap(it[2], it[10]);
  swap(it[15], it[11]);

  swap(it[12], it[12]);
  swap(it[13], it[9]);
  swap(it[6], it[14]);
  swap(it[3], it[15]);*/
  
  /*for (int i = 0; i < 16; i++)
  {
    qDebug() << it[i] << " " << i << " ";
  }*/
}
void AESCypher::MixColumns(QByteArray)
{

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


void AESCypher::InvMixColumns(QByteArray)
{
}



