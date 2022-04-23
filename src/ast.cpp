#include "../include/ast.h"

using namespace ast;

AST::AST() : m_current(0)
{
  std::list<tokenizer::Token> expression {};
  m_body.push_back(std::move(expression));
}

void AST::newExpression() noexcept
{
  std::list<tokenizer::Token> expression {};
  m_body.push_back(std::move(expression));
  m_current++;
};


void AST::pushToken(tokenizer::Token &&token) noexcept
{
    m_body[m_current].push_back(token);
};

const std::list<tokenizer::Token> &AST::getExpression(unsigned int position) const noexcept
{
    return m_body[position];
};

const ASTBody &AST::getBody()  const noexcept
{
    return m_body;
};

void AST::print()  const noexcept
{

    int n = 1;

    std::cout << "AST\n  ";
    for(auto &expression : m_body )
   {
       std::cout << "Expression " << n << "\n    | ";
       n++;
        
       for(auto &token : expression)
          std::cout << token.value << " -> ";

    std::cout << "\n";

   };
};

TEST_CASE("AST")
{

  tokenizer::Token token = {tokenizer::push, "push"};
  tokenizer::Token token2 = {tokenizer::int8, "int8"};
  auto ast = AST();

  ast.pushToken(std::move(token));
  ast.pushToken(std::move(token2));

  auto expression = ast.getExpression(0);

  int i = 0;

  for(auto &token : expression)
  {
    if(i == 0)
       CHECK(token.value == "push");

    if(i == 1)
       CHECK(token.value == "int8");

    i++;
  };

  ast.newExpression();

  auto expression2 = ast.getExpression(1);

  tokenizer::Token token3 = {tokenizer::assert, "assert"};
  tokenizer::Token token4 = {tokenizer::double_t, "double"};

  ast.pushToken(std::move(token3));
  ast.pushToken(std::move(token4));

  int j= 0;

  for(auto &token : expression)
  {
    if(j == 0)
       CHECK(token.value == "push");

    if(j == 1)
       CHECK(token.value == "int8");

    j++;
  };
};



