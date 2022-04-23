#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <iostream>

namespace exceptions
{
  enum ExceptionType {empty_stack, unexpected_token};
  class EmptyStack : public std::exception
 {
    public:
      static void          throwE(bool valid);
      static void          print();
      static ExceptionType getType();
  };

class UnexpectedToken : public std::exception
{
 public:
  [[noreturn]]  static void throwE();
  static               void print();
  static ExceptionType      getType();
};
}


#endif
