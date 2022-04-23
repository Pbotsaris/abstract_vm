#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <regex>
#include <iostream>
#include <string>
#include <array>
#include <utility>
#include "../include/doctest.h"
#include "../include/exceptions.h"

#define TOKENIZER_GRAMMAR_LENGTH 22

namespace tokenizer
{
  enum token_type {
    /* INSTR */
    push,                  /* 00 */
    pop,                   /* 01 */
    dump,                  /* 02 */
    assert,                /* 03 */
    add,                   /* 04 */
    sub,                   /* 05 */
    mul,                   /* 06 */
    div,                   /* 07 */
    mod,                   /* 08 */
    print,                 /* 09 */
    exit,                  /* 10 */
    /* TYPES */
    int8,                  /* 11 */
    int16,                 /* 12 */
    int32,                 /* 13 */
    float_t             ,  /* 14 */
    double_t,              /* 15 */
    /* SYNTAX */
    space,                 /* 16 */
    sep,                   /* 17 */
    parenthesis,           /* 18 */
    comment,               /* 19 */
    end_of_program,        /* 20 */
    /* VALUES */
    integers,              /* 21 */
    floats,                /* 22 */
    };
    
  struct Token {

    Token(const token_type type, const std::string &value);
    Token(Token &&other);

    token_type     type;
    std::string    value;

    void move(Token &&other)
    {
       type = other.type;
       value = other.value;
   };
  };
  
  class Tokenizer {
    private:
       struct            Private;
       const std::string m_text;
       size_t            m_textlen;
       int               m_cursor;
  
    public:
       Tokenizer (const std::string &test);

       tokenizer::Token nextToken();
  
  };
}
#endif
