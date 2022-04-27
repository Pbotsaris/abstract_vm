#include "../include/exceptions.h"

/* EMPTY STACK */

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

/* UNEXPECTED TOKEN */

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

/* UNEXPECTED END OF INPUT */

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

exceptions::ExceptionType exceptions::UnexpectedEndOfInput::getType()
{
  return exceptions::unexpected_end_of_input;
}

/* OVERFLOW */

std::string exceptions::Overflow::m_value;
std::string exceptions::Overflow::m_type;

template <>
void exceptions::Overflow::throwE<int8_t>(const std::string &value)
{
    m_value = value;
    m_type = std::string("int8");
    throw exceptions::Overflow();
};

template <>
void exceptions::Overflow::throwE<int16_t>(const std::string &value)
{
    m_value = value;
    m_type = std::string("int16");
    throw exceptions::Overflow();
};

template <>
void exceptions::Overflow::throwE<int32_t>(const std::string &value)
{
    m_value = value;
    m_type = std::string("int32");
    throw exceptions::Overflow();
};

void exceptions::Overflow::print()
{
  std::cout << "The value -> " << m_value << " overflows type '" << m_type << "'\n";
}

exceptions::ExceptionType exceptions::Overflow::getType()
{
  return exceptions::overflow;
}

/* BAD ASSERT */

std::string exceptions::BadAssert::m_left;
std::string exceptions::BadAssert::m_right;

void exceptions::BadAssert::throwE(const std::string &left, const std::string &right)
{
    m_left = left;
    m_right = right;
    throw exceptions::BadAssert();
};

void exceptions::BadAssert::print()
{
  std::cout << "Failed assert. Type or value  '" << m_left << "' does not match top of the stack value -> '" << m_right << "'\n";
}

exceptions::ExceptionType exceptions::BadAssert::getType()
{
  return exceptions::bad_assert;
}

/* BAD PRINT */

std::string exceptions::BadPrintType::m_type;

void exceptions::BadPrintType::throwE(const std::string &type)
{
    m_type = type;
    throw exceptions::BadPrintType();
};

void exceptions::BadPrintType::print()
{
  std::cout << "Attempting to Print operand type -> '" << m_type << "'. Print is only available for type 'Int8'.\n";
}

exceptions::ExceptionType exceptions::BadPrintType::getType()
{
  return exceptions::bad_print_type;
}
