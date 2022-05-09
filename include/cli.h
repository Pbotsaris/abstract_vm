#ifndef CLI_H
#define CLI_H

#include <fstream>
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
    bool                 m_istest;
    bool                 m_isfromfile;

    
    std::ifstream        m_filetext;
    /* for unit testing */
    std::istringstream   m_test_text;

    struct               Private;

  public:
    CLI();

    /* for file read & unit test */
    CLI(const char *text);
    CLI(const std::string &path);
   ~CLI() = default;

   void loadTextFromFile(const std::string &path);
   void mainLoop();

};

#endif
