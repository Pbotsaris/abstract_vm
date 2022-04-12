#include "../include/exceptions.h"

void exceptions::EmptyStack::tryCatch(bool valid)
{
  try {
    if(valid)
      throw exceptions::EmptyStack();
  } catch(exceptions::EmptyStack& err) {
    err.print();
  }
}

void exceptions::EmptyStack::print()
{
    std::cout << "The stack composed of less than two values when an arithmetic instruction was executed" << "\n";
}



