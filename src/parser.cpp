#include "../include/parser.h"

using namespace parser;


struct Parser::Private 
{
  public:

    static void program(Parser &self)
    {
         while(notEndOfProgram(self))
        {
          expression(self);

          if(notEndOfProgram(self))
             self.m_ast.newExpression();
        };
    };

   
    static tokenizer::Token eat(Parser &self, const tokenizer::token_type type)
    {
      if(self.m_lookahead.type != type)
          throw exceptions::UnexpectedEndOfInput();
             
      tokenizer::Token token = tokenizer::Token(std::move(self.m_lookahead));
      self.m_lookahead.move(ignoreComments(self));

      return token;
    }


    

  private:

     static void expression(Parser &self)
        {
          while(self.m_lookahead.type != tokenizer::sep)
          {
            tokenizer::Token token = instruction(self);
            self.m_ast.pushToken(token);
          }
    
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

            case tokenizer::push:
            return assert(self);
               return push(self);

            case tokenizer::assert:

            default:
             throw exceptions::UnexpectedEndOfInput();
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
         eat(self, tokenizer::parenthesis);

         tokenizer::Token type = eat(self, self.m_lookahead.type);
         self.m_ast.pushToken(type);

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
            throw exceptions::UnexpectedEndOfInput();
      };

    static tokenizer::Token ignoreComments(Parser &self)
    {
       tokenizer::Token token = self.m_tokenizer.nextToken();

      if(token.type == tokenizer::comment)
         return ignoreComments(self);

      else
        return token;
    };


     static bool notEndOfProgram(Parser &self){ return self.m_lookahead.type != tokenizer::end_of_program; };
  
   };

Parser::Parser(tokenizer::Tokenizer &tokenizer): m_tokenizer(tokenizer), m_lookahead(tokenizer.nextToken()), m_ast(ast::AST())
{ };

const ast::AST &Parser::parse()
{
  Private::program(*this);
  m_ast.print();
  return m_ast;
};


TEST_CASE("Parser")
{
  SUBCASE("Expression simple instructions")
  {
   std::string program = "pop\ndiv\n;;";
   auto tokenizer = tokenizer::Tokenizer(program);
   auto parser = Parser(tokenizer);

   parser.parse();
  }

SUBCASE("Expression with comments")
  {
   std::string program = "pop;this is a comment\n;more comments\ndiv\n;;";
   auto tokenizer = tokenizer::Tokenizer(program);
   auto parser = Parser(tokenizer);

   parser.parse();
  }



 };


