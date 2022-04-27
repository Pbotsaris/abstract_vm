#include "../include/cli.h"

using namespace tokenizer;
using namespace ast;
using namespace parser;
using namespace stack;


CLI::CLI() : 
    m_ast(AST()), 
    m_tokenizer(Tokenizer()),  
    m_parser(Parser(m_tokenizer, m_ast)), 
    m_stack(Stack())
{ };

struct CLI::Private
{
    static void printGreeting() { std::cout << "-- Welcome to Abstract VM\n"; };
};

void CLI::mainLoop()
{
  bool quit = false;
   
  Private::printGreeting();

  while(!quit)
  {

  std::string line;
  std::getline(std::cin, line);
  try
  {
       m_tokenizer.load(line);
       m_parser.parse();
       m_ast.print();
       //m_ast.reset();
  } 
   catch(exceptions::Exceptions &err)
  {
       err.print();
  }

  if(line == "quit")
      quit = true;
  };
}



