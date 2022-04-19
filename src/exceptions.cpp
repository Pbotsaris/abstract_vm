#include "../include/exceptions.h"

void exceptions::EmptyStack::throwE (bool valid)
{
  if(valid)
    throw exceptions::EmptyStack();
};

void exceptions::EmptyStack::tryCatch(bool valid)
{
  try {
    if(valid)
      throw exceptions::EmptyStack();
  } catch(exceptions::EmptyStack& err) {
    exceptions::EmptyStack::print();
  }
}

void exceptions::EmptyStack::print()
{
    std::cout << "The stack composed of less than two values when an arithmetic instruction was executed" << "\n";
}

exceptions::ExceptionType exceptions::EmptyStack::getType()
{
  return exceptions::empty_stack;
}

