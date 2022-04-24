#include "../include/parser.h"

using namespace parser;

/* PRIVATE IMPLEMENTATION */

struct Parser::Private 
{
  public:

    static void program(Parser &self)
    {
         while(notEndOfLine(self))
        {
          expression(self);

          if(notEndOfLine(self) && !self.m_ast.isExpressionEmpty())
             self.m_ast.newExpression();
        };
    };

   
    static tokenizer::Token eat(Parser &self, const tokenizer::token_type type)
    {
      if(self.m_lookahead.type != type)
        exceptions::UnexpectedEndOfInput::throwE(self.m_lookahead.value);
             
      tokenizer::Token token = std::move(self.m_lookahead);
      self.m_lookahead =  ignoreComments(self);

      return token;
    }

  private:
     static void expression(Parser &self)
     {
        while(notEndOfExpression(self))
        {
            tokenizer::Token token = instruction(self);
            self.m_ast.pushToken(token);
        }
         
         if(self.m_lookahead.type == tokenizer::end_of_line)
            return;
          
         eat(self, tokenizer::sep);
      };

     static tokenizer::Token instruction(Parser &self) 
     { 
        switch(self.m_lookahead.type)
        {
            case tokenizer::pop:
              return eat(self, tokenizer::pop); 

            case tokenizer::dump:
              return eat(self, tokenizer::dump); 

            case tokenizer::add:
              return eat(self, tokenizer::add); 

            case tokenizer::sub:
              return eat(self, tokenizer::sub); 

            case tokenizer::mul:
              return eat(self, tokenizer::mul); 

            case tokenizer::div:
              return eat(self, tokenizer::div); 

            case tokenizer::mod:
              return eat(self, tokenizer::mod); 

            case tokenizer::print:
               return eat(self, tokenizer::print); 

            case tokenizer::exit:
               return eat(self, tokenizer::exit); 

            case tokenizer::end_of_program:
               return eat(self, tokenizer::end_of_program); 

            case tokenizer::push:
               return push(self);

            case tokenizer::assert:
               return assert(self);

            default:
             exceptions::UnexpectedEndOfInput::throwE(self.m_lookahead.value);
         }
      
    };

     static tokenizer::Token push(Parser &self)
     {
         tokenizer::Token token = eat(self, tokenizer::push);
         self.m_ast.pushToken(token);

         return types(self);
     };


     static tokenizer::Token assert(Parser &self)
     {
          tokenizer::Token token = eat(self, tokenizer::assert);
          self.m_ast.pushToken(token);

          return types(self);
     };


     static tokenizer::Token types(Parser &self)
    { 
         tokenizer::Token type_token = eat(self, self.m_lookahead.type);
         self.m_ast.pushToken(type_token);

         eat(self, tokenizer::parenthesis);
         tokenizer::Token val = value(self);
         eat(self, tokenizer::parenthesis);

         return val;
    };

     static tokenizer::Token value(Parser &self)
     {
         if(self.m_lookahead.type == tokenizer::integers)
            return eat(self, tokenizer::integers);

         if(self.m_lookahead.type == tokenizer::floats)
            return eat(self, tokenizer::floats);

         else
            exceptions::UnexpectedEndOfInput::throwE(self.m_lookahead.value);
      };

    static tokenizer::Token ignoreComments(Parser &self)
    {
       tokenizer::Token token = self.m_tokenizer.nextToken();

      if(token.type == tokenizer::comment)
         return ignoreComments(self);

      else
        return token;
    };

   static bool notEndOfLine(Parser &self){ return self.m_lookahead.type != tokenizer::end_of_line; };

   static bool notEndOfExpression(Parser &self) 
   { 
      return self.m_lookahead.type != tokenizer::sep && self.m_lookahead.type != tokenizer::end_of_line; 
   };
};


/* CONSTRUCTOR */

Parser::Parser(tokenizer::Tokenizer &tokenizer): m_tokenizer(tokenizer), m_lookahead(tokenizer.nextToken()), m_ast(ast::AST())
{ };


/* PUBLIC */

const ast::AST &Parser::parse()
{
  Private::program(*this);
  return m_ast;
};

/* TESTS */

TEST_CASE("Parser")
{
  SUBCASE("instructions Expression without arguments")
  {
   std::string program    = "pop\ndiv\n;;";
   auto tokenizer         = tokenizer::Tokenizer(program);
   auto parser            = Parser(tokenizer);

   const auto &ast        = parser.parse();
   const auto &exp        = ast.getExpressionAt(0);
   const auto &exp2       = ast.getExpressionAt(1);

   CHECK(exp.back().type == tokenizer::pop);
   CHECK(exp2.back().type == tokenizer::div);
  }

  SUBCASE("Instruction Expression with comments")
  {
   std::string program = "pop;this is a comment\n;more comments\ndiv";
   auto tokenizer      = tokenizer::Tokenizer(program);
   auto parser         = Parser(tokenizer);

   const auto &ast      = parser.parse();
   const auto &exp      = ast.getExpressionAt(0);
   const auto &exp2     = ast.getExpressionAt(1);

   CHECK(exp.back().type == tokenizer::pop);
   CHECK(exp2.back().type == tokenizer::div);
  }

 SUBCASE("Expression with arguments and integers")
 {
   std::string program = "assert int8(10)\npush int16(20)";
   auto tokenizer      = tokenizer::Tokenizer(program);
   auto parser         = Parser(tokenizer);

   const auto &ast      = parser.parse();
   const auto &exp      = ast.getExpressionAt(0);
   const auto &exp2     = ast.getExpressionAt(1);

   int i = 0, j = 0;

   for(auto &token : exp)
   {
     if(i == 0)
       CHECK(token.type == tokenizer::assert);
     if(i == 1)
       CHECK(token.type == tokenizer::int8);
     if(i == 2)
     {
       CHECK(token.type == tokenizer::integers);
       CHECK(token.value == "10");
     }
     i++;
   };

   for(auto &token : exp2)
   {
     if(j == 0)
       CHECK(token.type == tokenizer::push);
     if(j == 1)
       CHECK(token.type == tokenizer::int16);
     if(j == 2)
     {
       CHECK(token.type == tokenizer::integers);
       CHECK(token.value == "20");
     }
     j++;
   };
 }

 SUBCASE("Expression with arguments and floats")
 {
   std::string program = "assert double(10.203)\npush float(20.43)";
   auto tokenizer      = tokenizer::Tokenizer(program);
   auto parser         = Parser(tokenizer);

   const auto &ast      = parser.parse();
   const auto &exp      = ast.getExpressionAt(0);
   const auto &exp2     = ast.getExpressionAt(1);

   int i = 0, j = 0;

   for(auto &token : exp)
   {
     if(i == 0)
       CHECK(token.type == tokenizer::assert);
     if(i == 1)
       CHECK(token.type == tokenizer::double_t);
     if(i == 2)
     {
       CHECK(token.type == tokenizer::floats);
       CHECK(token.value == "10.203");
     }
     i++;
   };

   for(auto &token : exp2)
   {
     if(j == 0)
       CHECK(token.type == tokenizer::push);
     if(j == 1)
       CHECK(token.type == tokenizer::float_t);
     if(j == 2)
     {
       CHECK(token.type == tokenizer::floats);
       CHECK(token.value == "20.43");
     }
     j++;
   };
 }

 SUBCASE("Expression with arguments and end of program")
  {
   std::string program = "push int32(1000)\n;;";
   auto tokenizer      = tokenizer::Tokenizer(program);
   auto parser         = Parser(tokenizer);

   const auto &ast      = parser.parse();
   const auto &exp      = ast.getExpressionAt(0);
   const auto &exp2     = ast.getExpressionAt(1);

  int i = 0;

   for(auto &token : exp)
   {
     if(i == 0)
       CHECK(token.type == tokenizer::push);
     if(i == 1)
       CHECK(token.type == tokenizer::int32);
     if(i == 2)
     {
       CHECK(token.type == tokenizer::integers);
       CHECK(token.value == "1000");
     }
     i++;
   };

    CHECK(exp2.back().type == tokenizer::end_of_program);
  }

  SUBCASE("Every instruction")
  {
    using TestPair = std::pair<std::string, tokenizer::token_type>;

    TestPair  pop ("pop", tokenizer::pop);
    TestPair  dump ("dump", tokenizer::dump);
    TestPair  add ( "add", tokenizer::add);
    TestPair  sub ("sub", tokenizer::sub);
    TestPair  mul ("mul", tokenizer::mul);
    TestPair  div ("div", tokenizer::div);
    TestPair  print ("print", tokenizer::print);
    TestPair  exit ("exit", tokenizer::exit);
    std::array<TestPair, 8> program = {

      pop,
      dump,
      add,
      sub,
      mul,
      div,
      print,
      exit,
    };
      
    for(auto &instr : program)
    {
       auto tokenizer      = tokenizer::Tokenizer(instr.first);
       auto parser         = Parser(tokenizer);

       const auto &ast      = parser.parse();
       const auto &exp      = ast.getExpressionAt(0);

      CHECK(exp.back().type == instr.second);
    };

  } 
};


