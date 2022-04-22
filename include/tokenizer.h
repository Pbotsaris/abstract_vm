#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <regex>
#include <iostream>
#include <string>
#include <array>
#include <utility>
#include "../include/doctest.h"
#include "../include/exceptions.h"

namespace tokenizer
{
enum token_type {
  /* INSTR */
  push, pop, dump, assert, add, sub, mul, div, mod, print, exit,
  /* TYPES */
  int8, int16, int32,
  /* SYNTAX */
  space, sep, parenthesis, comment, end_of_program,
  /* VALUES */
  integers, floats,
  };
  
struct Token {
  token_type type;
  const std::string value;
};

class Tokenizer {
 private:
  struct Private;
  std::string m_text;
  size_t m_textlen;
  int m_cursor;

 public:
  Tokenizer (std::string &test);

  const tokenizer::Token nextToken();


};
}

#endif
