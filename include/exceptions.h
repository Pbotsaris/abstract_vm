#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <iostream>
#include <string>

namespace exceptions
{
  enum ExceptionType {empty_stack, unexpected_token, unexpected_end_of_input, overflow};

  class Exceptions : public std::exception {

    public:
      virtual void          print() = 0;
      virtual ExceptionType getType() = 0;
 };


  class EmptyStack : public  Exceptions
 {
    public:
      static void          throwE(bool valid);
      void                 print() override;
      ExceptionType        getType() override;
  };

  class UnexpectedToken : public Exceptions
  {
  
   public:
    static std::string m_token;
    [[noreturn]]  static void throwE(const std::string &token);
    void                      print() override;
    ExceptionType             getType() override;
  };
  
  class UnexpectedEndOfInput : public Exceptions
  {
   public:
    static std::string m_token;
  
    [[noreturn]]  static void throwE(const std::string &token);
    void                      print() override;
    ExceptionType            getType() override;
  };

    class Overflow : public Exceptions
  {
   public:
    static std::string m_value;
    static std::string m_type;

    template <typename T>
    [[noreturn]]  static void throwE(const std::string &value);

    void                      print() override;
    ExceptionType            getType() override;
  };

}
#endif
