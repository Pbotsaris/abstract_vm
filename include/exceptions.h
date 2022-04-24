#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <iostream>
#include <string>

namespace exceptions
{
  enum ExceptionType {empty_stack, unexpected_token};

   class Exceptions : public std::exception {
      static void          print();
      static ExceptionType getType();
 };


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
  static std::string m_token;
  [[noreturn]]  static void throwE(const std::string &token);
  static               void print();
  static ExceptionType      getType();
};

class UnexpectedEndOfInput : public std::exception
{
 public:
  static std::string m_token;

  [[noreturn]]  static void throwE(const std::string &token);
  static               void print();
  static ExceptionType      getType();
};

}


#endif
