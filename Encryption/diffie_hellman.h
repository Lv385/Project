#pragma once
#include <iostream>
#include <QVector>
class Key {
public:

  Key();

  int SetNewPow();
  void SetNewMyCode();
  void SetFriendCode(int B);
  int GetKey();
private:
  static const int p = 23;
  static  const int g = 17;// p and g public nums
  //static const int a;
  int my_code; // (g^a)%p or(g^a) mod p
  int friend_code; //recieved from B 
  static  int my_pow;
  //g, p, a; should be simple numbers
};