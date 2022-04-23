#ifndef AST_H
#define AST_H

#include <vector>
#include <list>
#include "../include/tokenizer.h"

namespace ast
{
  using ASTBody = std::vector<std::list<tokenizer::Token>>;

  class AST
  {
      private:
        ASTBody m_body;
        unsigned int m_current;
  
    public:
  
       AST();
  
       void                                newExpression() noexcept;
       void                                pushToken(tokenizer::Token &&token) noexcept;
       const std::list<tokenizer::Token>  &getExpression(unsigned int position) const noexcept;
       const ASTBody                      &getBody() const noexcept;
       void                                print() const noexcept;
  };
};


#endif
