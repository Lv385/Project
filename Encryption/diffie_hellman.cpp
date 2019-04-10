#include "diffie_hellman.h"

template <typename T> int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

template <class T, class U> auto safe_pow(T val, U p) -> decltype(pow(val, p)) {
  return pow(abs(val), p) * sgn(val);
}


Key::Key()
{
}

int Key::SetNewPow()
{
  my_pow = int(rand()%5000);
  return my_pow;
}

void Key::SetNewMyCode()
{
  my_code = int(pow(p, my_pow)) % g;
}

void Key::SetFriendCode(int B)
{
  friend_code = B;
}

int Key::GetKey()
{
  return int(pow(friend_code, my_pow));

}

