#ifndef CLI_H
#define CLI_H

#include "../src/operands.cpp"
#include "evaluator.h"
#include "stack.h"
#include "parser.h"

class CLI
{
  private:
    ast::AST             m_ast;
    tokenizer::Tokenizer m_tokenizer;
    parser::Parser       m_parser;
    stack::Stack         m_stack;
    evaluator::Evaluator m_eval;
    bool                 m_exit;
    struct               Private;

    /* members used for unit test only */
    bool                 m_test;
    std::istringstream   m_test_line;

  public:
    CLI();

    /* constructor used for unit test only */
    CLI(const char *line);
   ~CLI() = default;

   void mainLoop();

};

#endif
