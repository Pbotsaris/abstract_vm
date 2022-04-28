#ifndef EVALUATOR_H 
#define EVALUATOR_H
#include <list>
#include <cmath>
#include "../include/stack.h"
#include "../include/tokenizer.h"

namespace evaluator
{

    class Evaluator
    {
    private:
          stack::Stack m_stack;
          struct Private;
    
    public:

         Evaluator() = default;
         ~Evaluator() = default;
       
        const IOperand* stackTop();
        
        void push(const std::list<tokenizer::Token> &expression);
        void assert(const std::list<tokenizer::Token> &expression);
    
        void pop();
        void dump();
    
        void add();
        void sub();
    
        void mul();
        void div();
        void mod();
        
        void print();
    };

}

#endif 
