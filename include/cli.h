#ifndef CLI_H
#define CLI_H

#include "../src/operands.cpp"
//#include "evaluator.h"
#include "stack.h"
#include "parser.h"

class CLI
{
  private:
    ast::AST             m_ast;
    tokenizer::Tokenizer m_tokenizer;
    parser::Parser       m_parser;
    stack::Stack         m_stack;
 //   evaluator::Evaluator m_evaluator;
  
    struct               Private;

  public:
    CLI();
   ~CLI() = default;

   void mainLoop();

};




#endif
