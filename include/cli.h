#ifndef CLI_H
#define CLI_H

//#include "../include/exceptions.h"
#include "../src/operands.cpp"
#include "stack.h"
#include "parser.h"

class CLI
{
  private:
    ast::AST m_ast;
    tokenizer::Tokenizer m_tokenizer;
    parser::Parser m_parser;
    stack::Stack m_stack;
    struct Private;

  public:
    CLI();
   ~CLI() = default;

   void mainLoop();

};




#endif
