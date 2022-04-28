#include "../include/cli.h"

using namespace tokenizer;
using namespace ast;
using namespace parser;
using namespace stack;
//using namespace evaluator;

CLI::CLI() : 
    m_parser(Parser(m_tokenizer, m_ast)),
    m_exit(false)
{ };

struct CLI::Private
{
    static void printGreeting() { std::cout << "-- Welcome to Abstract VM\n"; };

    static void evaluate(CLI &self)
    {
        for(auto &expression : self.m_ast.getBody())
           runInstruction(self, expression);
    };

    static void runInstruction(CLI &self, const std::list<tokenizer::Token> &expression)
    {
      switch(expression.front().type)
      {
          case tokenizer::push:
            self.m_eval.push(expression);
            return;

          case tokenizer::pop:
            self.m_eval.pop();
            return;

          case tokenizer::dump:
            self.m_eval.dump();
            return;

          case tokenizer::assert:
            self.m_eval.assert(expression);
            return;

          case tokenizer::add:
            self.m_eval.add();
            return;

          case tokenizer::sub:
            self.m_eval.sub();
            return;

          case tokenizer::mul:
            self.m_eval.mul();
            return;

          case tokenizer::div:
            self.m_eval.div();
            return;

          case tokenizer::print:
            self.m_eval.print();
            return;

          case tokenizer::exit:
            return;

         case tokenizer::end_of_program:
            return;

          default:
             throw std::exception();
      };

    };

    static bool readyToEvaluate(CLI &self)
    {
     return !self.m_ast.empty() && self.m_ast.lastToken().type == tokenizer::end_of_program;
    };
};

void CLI::mainLoop()
{
  Private::printGreeting();
  m_exit = false;

  while(!m_exit)
  {
  std::string line;
  std::getline(std::cin, line);
  try
  {
       m_tokenizer.load(line);
       m_parser.parse();

       if(Private::readyToEvaluate(*this))
       {
          Private::evaluate(*this);
          m_ast.reset();
       }
  } 
   catch(exceptions::Exceptions &err)
  {
       err.print();

       if(err.getType() == exceptions::overflow)
          m_ast.reset();
  }

  if(line == "exit")
       m_exit = true;

  };
}



