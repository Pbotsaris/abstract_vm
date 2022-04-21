#include "../include/exceptions.h"

void exceptions::EmptyStack::throwE (bool valid)
{
  if(valid)
    throw exceptions::EmptyStack();
};


void exceptions::EmptyStack::print()
{
    std::cout << "The stack composed of less than two values when an arithmetic instruction was executed" << "\n";
}

exceptions::ExceptionType exceptions::EmptyStack::getType()
{
  return exceptions::empty_stack;
}

void exceptions::UnexpectedToken::throwE ()
{
    throw exceptions::UnexpectedToken();
};

void exceptions::UnexpectedToken::print()
{
  std::cout << "Unexpected Token" << "\n";
}

exceptions::ExceptionType exceptions::UnexpectedToken::getType()
{
  return exceptions::unexpected_token;
}

