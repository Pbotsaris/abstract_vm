#ifndef STACK_H
#define STACK_H
#include "../include/IOperand.h"
#include "../include/exceptions.h"

#include <stack>
#include <any>

//template <typename Head, typename... Tail>
//struct sel
//: std::conditional_t<Head::value, Head, sel<Tail...>>
//{ };
//
//template<eOperandType op_type>
//struct type_cast
//{
//     using type = std::cond>;
//};


class Stack 
{
  private: 
    std::stack<std::any> m_stack;

  public:
    struct type_cast;
    void                               push(IOperandBase* operand);
    auto                               pop();
};




#endif
