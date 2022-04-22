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
enum token_type {instr, value, integer, fpoint, sep, comment, EOP, err};

struct Token {
  token_type type;
  const std::string &value;
};

class Tokenizer {
 private:
  struct Private;
  std::string m_text;
  size_t m_textlen;
  int m_cursor;

 public:
  Tokenizer (std::string &test);

  tokenizer::Token nextToken();

};
}

#endif
