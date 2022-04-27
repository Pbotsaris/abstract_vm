#include "../include/stack.h"

using namespace stack;

Stack::~Stack ()
{
  while (!m_stack.empty ())
    {
      const IOperand *operand = m_stack.top ();
      m_stack.pop ();
      delete operand;
    }
}
void Stack::push (const IOperand *operand)

{
  m_stack.push (operand);
};

const IOperand *Stack::pop ()
{
  exceptions::EmptyStack::throwE (m_stack.empty ());

  const IOperand *top = m_stack.top ();
  m_stack.pop ();
  return top;
};

//TEST_CASE("Stack") // NOLINT(cert-err58-cpp)
//{
//  Stack s = Stack ();
//  s.push (factory::factory.create (Int8_t, "8"));
//  s.push (factory::factory.create (Int32_t, "53"));
//  s.push (factory::factory.create (Double_t, "2.202"));
//
//  auto r = s.pop ();
//  auto r2 = s.pop ();
//  auto r3 = s.pop ();
//
//  SUBCASE("Pushing and Popping stack")
//  {
//      CHECK(r->toString () == "2.202");
//      CHECK(r2->toString () == "53");
//      CHECK(r3->toString () == "8");
//  }
//
//  SUBCASE("Handles EmptyStack Exception")
//    {
//      try
//        {
//          s.pop();
//        }
//      catch (exceptions::Exceptions &err)
//        {
//          CHECK(err.getType() == exceptions::empty_stack);
//        }
//    }
//
//  delete r;
//  delete r2;
//  delete r3;
//}

