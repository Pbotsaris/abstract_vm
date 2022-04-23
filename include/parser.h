#ifndef PARSER_H
#define PARSER_H
#include "../include/ast.h"
#include "../include/exceptions.h"

namespace parser
{
    class Parser
    {
        private:
           struct               Private;
           tokenizer::Tokenizer &m_tokenizer;
           tokenizer::Token     m_lookahead;
           ast::AST             m_ast;
  
        public:
           Parser(tokenizer::Tokenizer &tokenizer);
         
          const ast::AST &parse();
    };
}


#endif
