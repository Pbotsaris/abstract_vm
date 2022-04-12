#include "../include/stack.h"

void Stack::push(IOperandBase* operand)
{
  m_stack.push(operand);
};

auto Stack::pop()
{
  exceptions::EmptyStack::tryCatch(m_stack.empty());
  
  auto operand = std::move(m_stack.top());
  m_stack.pop();

  return operand;
}

/* TEST */
TEST_CASE("Stack")

{
 Stack stack  = Stack();

 // IOperand<int32_t> n1 = IOperand<int32_t>(10);

 // IOperand<int16_t>* item2= new IOperand<int16_t>(10);
 // IOperand<int16_t>* item3= new IOperand<int16_t>(10);
 // IOperand<int16_t>* item4 = new IOperand<int16_t>(10);

// stack.push(item1);
// stack.push(item2);
// stack.push(item3);
//
// delete item1;
//  delete item2;
 // delete item3;
//  delete item4;

 //  stack.push(std::move(item4));

//auto i4 = stack.pop();

//const eOperandType t = i4->getType();

 // i4->getValue();
  
//IOperand<int8_t>::cast(std::move(i4));

  //CHECK( i4->getType() == 1);

}
