#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <iostream>

namespace exceptions
{
  enum ExceptionType {empty_stack};
  class EmptyStack : public std::exception
 {
    public:
      static void throwE(bool valid);
      static void tryCatch(bool valid);
      static void print();
      static ExceptionType getType();
  };
}


#endif
