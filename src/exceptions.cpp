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

std::string exceptions::UnexpectedToken::m_token;

void exceptions::UnexpectedToken::throwE (const std::string &token)
{
    m_token = token;
    throw exceptions::UnexpectedToken();
};

void exceptions::UnexpectedToken::print()
{
  std::cout << "Unexpected Token -> '" << m_token << "' \n";
}

exceptions::ExceptionType exceptions::UnexpectedToken::getType()
{
  return exceptions::unexpected_token;
}

std::string exceptions::UnexpectedEndOfInput::m_token;

void exceptions::UnexpectedEndOfInput::throwE(const std::string &token)
{
    m_token = token;
    throw exceptions::UnexpectedEndOfInput();
};


void exceptions::UnexpectedEndOfInput::print()
{
  std::cout << "Unexpected end onf input: '" << m_token << "'\n";
}



