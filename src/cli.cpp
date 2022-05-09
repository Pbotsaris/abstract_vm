#include "../include/cli.h"

using namespace tokenizer;
using namespace ast;
using namespace parser;
using namespace stack;

CLI::CLI() : 
    m_parser(Parser(m_tokenizer, m_ast)),
    m_exit(false),
    m_istest(false),
    m_isfromfile(false),
    m_test_text("")
{ };

/*  unit tests */
CLI::CLI(const char *text) : 
    m_parser(Parser(m_tokenizer, m_ast)),
    m_exit(false),
    m_istest(true),
    m_isfromfile(false),
    m_test_text(text)
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

          case tokenizer::mod:
            self.m_eval.mod();
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

    static bool resetAST(exceptions::Exceptions &err)
    {
     return err.getType() == exceptions::overflow ||
            err.getType() == exceptions::empty_stack ||
            err.getType() == exceptions::bad_print_type;
    }

    static bool resetExpression(exceptions::Exceptions &err)
    {
     return err.getType() == exceptions::unexpected_token || err.getType() == exceptions::unexpected_end_of_input;
    }

    static bool isEOF(CLI &self, std::string &line)
    {
      return self.m_isfromfile && line == "";
    };
};

void CLI::loadTextFromFile(const std::string &path)
{
    m_isfromfile = true;
    m_filetext = std::ifstream(path);
};

void CLI::mainLoop()
{
  if(!m_istest && !m_isfromfile)
    Private::printGreeting();

  while(!m_exit)
  {
  std::string line;

  if(!m_istest)
      std::getline(m_isfromfile ? m_filetext : std::cin, line); 
  else
      std::getline(m_test_text, line); 

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

       if(Private::resetExpression(err))
           m_ast.deleteCurrentExpression();

       if(Private::resetAST(err))
          m_ast.reset();
  }

  if(line == "exit" || Private::isEOF(*this, line))
       m_exit = true;

  };
}


TEST_CASE("CLI")
{

    
  SUBCASE("push and dump")
  {

    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    const char *line = "push int8(10)\npush int8(20)\ndump\n;;\nexit\n";

    CLI cli(line);
    cli.mainLoop();

    std::string res = buffer.str();
    std::cout.rdbuf(prevcoutbuf);

    CHECK(res == "20\n10\n");

  }


 SUBCASE("add and dump")
  {

    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    const char *line = "push int16(200)\npush int16(200)\nadd\ndump\n;;\nexit\n";

    CLI cli(line);
    cli.mainLoop();

    std::string res = buffer.str();
    std::cout.rdbuf(prevcoutbuf);

    CHECK(res == "400\n");
  }


SUBCASE("sub and dump")
  {

    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    const char *line = "push int32(2000)\npush int16(1000)\nsub\ndump\n;;\nexit\n";

    CLI cli(line);
    cli.mainLoop();

    std::string res = buffer.str();
    std::cout.rdbuf(prevcoutbuf);

    CHECK(res == "1000\n");
  }


SUBCASE("div and dump")
  {
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    const char *line = "push int8(30)\npush double(2.4)\ndiv\ndump\n;;\nexit\n";

    CLI cli(line);
    cli.mainLoop();

    std::string res = buffer.str();
    std::cout.rdbuf(prevcoutbuf);

    CHECK(res == "12.5\n");
  }

SUBCASE("mul and dump")
  {
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    const char *line = "push int8(30)\npush double(3.5)\nmul\ndump\n;;\nexit\n";

    CLI cli(line);
    cli.mainLoop();

    std::string res = buffer.str();
    std::cout.rdbuf(prevcoutbuf);

    CHECK(res == "105\n");
  }

SUBCASE("mod and dump")
  {
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    const char *line = "push int8(30)\npush int8(7)\nmod\ndump\n;;\nexit\n";

    CLI cli(line);
    cli.mainLoop();

    std::string res = buffer.str();
    std::cout.rdbuf(prevcoutbuf);

    CHECK(res == "2\n");
  }

SUBCASE("pop and dump")
  {
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    const char *line = "push int8(30)\npush int8(7)\ndump\npop\ndump\n;;\nexit\n";

    CLI cli(line);
    cli.mainLoop();

    std::string res = buffer.str();
    std::cout.rdbuf(prevcoutbuf);

    CHECK(res == "7\n30\n30\n");
  }

SUBCASE("push and print")
  {
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    const char *line = "push int8(65)\nprint\n;;\nexit\n";

    CLI cli(line);
    cli.mainLoop();

    std::string res = buffer.str();
    std::cout.rdbuf(prevcoutbuf);

    CHECK(res == "A\n");
  }


  SUBCASE("bad type assert")
  {
    std::string expected = "Failed assert. Type or value 'Int16' does not match top of the stack -> 'Int8'\n";
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    const char *line = "push int8(8)\nassert int16(8)\n;;\nexit\n";

    CLI cli(line);
    cli.mainLoop();

    std::string res = buffer.str();
    std::cout.rdbuf(prevcoutbuf);

    CHECK(res == expected);
  }

  SUBCASE("bad value assert")
  {
    std::string expected = "Failed assert. Type or value '9' does not match top of the stack -> '8'\n";
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    const char *line = "push int16(8)\nassert int16(9)\n;;\nexit\n";

    CLI cli(line);
    cli.mainLoop();

    std::string res = buffer.str();
    std::cout.rdbuf(prevcoutbuf);

    CHECK(res == expected);
  }

 SUBCASE("syntax error - Unexpected Token")
  {
    std::string expected = "Unexpected end onf input: ''\n";
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    const char *line = "push int16\n;;\nexit\n";

    CLI cli(line);
    cli.mainLoop();

    std::string res = buffer.str();
    std::cout.rdbuf(prevcoutbuf);

    CHECK(res == expected);
  }

SUBCASE("syntax error - somehting")
  {
    std::string expected = "Unexpected Token -> 'dogs' \n";
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    const char *line = "push dogs\n;;\nexit\n";

    CLI cli(line);
    cli.mainLoop();

    std::string res = buffer.str();
    std::cout.rdbuf(prevcoutbuf);

    CHECK(res == expected);
  }

SUBCASE("Type error: Overflow")
  {
    std::string expected = "The value -> 300 overflows type 'int8'\n";
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    const char *line = "push int8(300)\n;;\nexit\n";

    CLI cli(line);
    cli.mainLoop();

    std::string res = buffer.str();
    std::cout.rdbuf(prevcoutbuf);

    CHECK(res == expected);
  }

SUBCASE("Type error: Overflow during operation")
  {
    std::string expected = "The value -> 200000000 overflows type 'int16'\n";
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    const char *line = "push int16(10000)\npush int16(20000)\nmul\n;;\nexit\n";

    CLI cli(line);
    cli.mainLoop();

    std::string res = buffer.str();
    std::cout.rdbuf(prevcoutbuf);

    CHECK(res == expected);
  }

SUBCASE("Stack error: pop on empty stack")
  {
    std::string expected = "The stack is empty. The operation was not completed.\n";
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    const char *line = "push int16(10000)\npop\npop\n;;\nexit\n";

    CLI cli(line);
    cli.mainLoop();

    std::string res = buffer.str();
    std::cout.rdbuf(prevcoutbuf);

    CHECK(res == expected);
  }

SUBCASE("Stack error: operate on single stack item")
  {
    std::string expected = "The stack is empty. The operation was not completed.\n";
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    const char *line = "push int16(10000)\nadd\n;;\nexit\n";

    CLI cli(line);
    cli.mainLoop();

    std::string res = buffer.str();
    std::cout.rdbuf(prevcoutbuf);

    CHECK(res == expected);
  }

}



