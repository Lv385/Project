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
  static  const int g = 17;
  static const int a;
  int my_code;
  int friend_code;
  static  int my_pow;
  
};