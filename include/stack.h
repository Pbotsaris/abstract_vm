#ifndef STACK_H
#define STACK_H
#include "../include/factory.h"
#include "../include/exceptions.h"

#include <stack>

class Stack
{
  private:
    std::stack<const IOperand*> m_stack;

  public:
    ~Stack();
    void               push(const IOperand* operand);
    const IOperand*    pop();

};




#endif
