#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <iostream>

namespace exceptions
{
  class EmptyStack : public std::exception
 {
    public:
      static void tryCatch(bool valid);
  
      void print();
  };
}


#endif
