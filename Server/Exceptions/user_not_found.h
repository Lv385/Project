#pragma once
#include <exception>

class UserNotFound : public std::exception {
 public:
  const char* what() const throw() {
    return "Exception: No such user in DB!"; 
  }
};