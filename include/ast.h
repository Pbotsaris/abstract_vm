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
        int m_current;
  
    public:
  
       AST();
  
       void                                newExpression() noexcept;
       void                                pushToken(tokenizer::Token &token) noexcept;
       const ASTBody                      &getBody() const noexcept;
       const std::list<tokenizer::Token>  &getExpressionAt(unsigned int position) const noexcept;
       bool                                isExpressionEmpty() const noexcept;
       void                                reset() noexcept;
       void                                print() const noexcept;
       const tokenizer::Token             &lastToken()const noexcept;
       bool                                empty() const noexcept;
  };
};


#endif
