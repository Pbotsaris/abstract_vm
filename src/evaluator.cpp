#include "../include/evaluator.h"

using namespace evaluator;

struct Evaluator::Private
{

    static eOperandType selectType(const std::list<tokenizer::Token> &expression)
    {

    for(auto &token : expression) 
      {
        if(token.type == tokenizer::int8)
           return Int8_t;

        if(token.type == tokenizer::int16)
             return Int16_t;

        if(token.type == tokenizer::int32)
             return Int32_t;

        if(token.type == tokenizer::float_t)
             return Float_t;

         if(token.type == tokenizer::double_t)
             return Double_t;
     };

      return Int32_t;

    };
    
    static std::string typeToString(eOperandType type)
    {
      switch(type)
      {
          case Int8_t:
           return "Int8";

          case Int16_t:
           return "Int16";

          case Int32_t:
           return "Int32";

          case Float_t:
           return "Float";

          case Double_t:
           return "Double";
      }
    };

    static void performOperation(Evaluator &self, const IOperand *(*lambda)(const IOperand *lhs, const IOperand *rhs))
    {
      const IOperand *rhs = self.m_stack.pop();;
      const IOperand *lhs;

     try
      {
          lhs = self.m_stack.pop();
      }
      catch(exceptions::Exceptions &err)
      {
          self.m_stack.push(rhs);
          throw;
      }
  
      try
      {
         auto *res = lambda(lhs, rhs);
         self.m_stack.push(res);
      }
      catch(exceptions::Exceptions &err)
      {
          delete rhs;
          delete lhs;
          throw;
      }

     delete rhs;
     delete lhs;
  }

};

const IOperand *Evaluator::stackTop()
{
  return m_stack.top();
}

void Evaluator::push(const std::list<tokenizer::Token> &expression)
{
    std::string value = std::move(expression.back().value); 
    IOperand *operand = factory::factory.create(Private::selectType(expression), value);
    m_stack.push(operand);
};


void Evaluator::assert(const std::list<tokenizer::Token> &expression)
{
    std::string value = std::move(expression.back().value);
    eOperandType type = Private::selectType(expression);

    if(value != m_stack.top()->toString())
        exceptions::BadAssert::throwE(value, m_stack.top()->toString());


    if(type != m_stack.top()->getType())
       exceptions::BadAssert::throwE(Private::typeToString(type),
                                     Private::typeToString(m_stack.top()->getType()));
}

void Evaluator::pop()
{
   auto *operand = m_stack.pop();
   delete operand;
};

void Evaluator::dump()
{
    std::list<const IOperand*> temp;
    
    while(!m_stack.empty())
    {
      auto *operand = m_stack.pop();
      std::cout << operand->toString() << "\n";
      temp.push_back(operand);
    };

   while(!temp.empty())
   {
      auto *operand = temp.back();
      m_stack.push(std::move(operand));
      temp.pop_back();
   };
};

void Evaluator::add()
{
   auto sum = [](const IOperand *lhs, const IOperand *rhs) -> const IOperand*
   {
      return (*lhs) + (*rhs);
   };

   Private::performOperation(*this, sum);
};

void Evaluator::sub()
{
   auto subtract = [](const IOperand *lhs, const IOperand *rhs) -> const IOperand*
   {
      return (*lhs) - (*rhs);
   };

   Private::performOperation(*this, subtract);

};


void Evaluator::mul()
{
  auto multiplication = [](const IOperand *lhs, const IOperand *rhs) -> const IOperand*
   {
      return (*lhs) * (*rhs);
   };

   Private::performOperation(*this, multiplication);
};


void Evaluator::div()
{
  auto division = [](const IOperand *lhs, const IOperand *rhs) -> const IOperand*
   {
      return (*lhs) / (*rhs);
   };

   Private::performOperation(*this, division);
};

void Evaluator::mod()
{
  auto modulo = [](const IOperand *lhs, const IOperand *rhs) -> const IOperand*
   {
      return (*lhs) % (*rhs);
   };

   Private::performOperation(*this, modulo);
};

void Evaluator::print()
{
    auto *operand = m_stack.pop();
    
    if(operand->getType() != Int8_t)
    {
       m_stack.push(operand);
       exceptions::BadPrintType::throwE(Private::typeToString(operand->getType()));
    }
                                     
    char c = static_cast<char>(std::stoi(operand->toString()));
    std::cout << c << "\n";
    
    m_stack.push(operand);
};


TEST_CASE("evaluator")
{
  SUBCASE("push int8")
  {

    tokenizer::Token t1 = {tokenizer::push, "push"};
    tokenizer::Token t2 = {tokenizer::int8, "int8"};
    tokenizer::Token t3 = {tokenizer::integers, "10"};

    std::list<tokenizer::Token> expression;

    expression.push_back(std::move(t1));
    expression.push_back(std::move(t2));
    expression.push_back(std::move(t3));

    Evaluator eval;
    eval.push(expression);

    auto *operand = eval.stackTop();

    CHECK(operand->getType() == Int8_t);
    CHECK(operand->toString() == "10");

  }

  SUBCASE("push int16")
  {

    tokenizer::Token t1 = {tokenizer::push, "push"};
    tokenizer::Token t2 = {tokenizer::int16, "int16"};
    tokenizer::Token t3 = {tokenizer::integers, "10"};

    std::list<tokenizer::Token> expression;

    expression.push_back(std::move(t1));
    expression.push_back(std::move(t2));
    expression.push_back(std::move(t3));

    Evaluator eval;
    eval.push(expression);

    auto *operand = eval.stackTop();

    CHECK(operand->getType() == Int16_t);
    CHECK(operand->toString() == "10");

  }

  SUBCASE("push int32")
  {

    tokenizer::Token t1 = {tokenizer::push, "push"};
    tokenizer::Token t2 = {tokenizer::int32, "int32"};
    tokenizer::Token t3 = {tokenizer::integers, "10"};

    std::list<tokenizer::Token> expression;

    expression.push_back(std::move(t1));
    expression.push_back(std::move(t2));
    expression.push_back(std::move(t3));

    Evaluator eval;
    eval.push(expression);

    auto *operand = eval.stackTop();

    CHECK(operand->getType() == Int32_t);
    CHECK(operand->toString() == "10");

  }

  SUBCASE("push float")
  {
    tokenizer::Token t1 = {tokenizer::push, "push"};
    tokenizer::Token t2 = {tokenizer::float_t, "float"};
    tokenizer::Token t3 = {tokenizer::floats, "10.10"};

    std::list<tokenizer::Token> expression;

    expression.push_back(std::move(t1));
    expression.push_back(std::move(t2));
    expression.push_back(std::move(t3));

    Evaluator eval;
    eval.push(expression);

    auto *operand = eval.stackTop();

    CHECK(operand->getType() == Float_t);
    CHECK(operand->toString() == "10.1");

  }

  SUBCASE("push double")
  {
    tokenizer::Token t1 = {tokenizer::push, "push"};
    tokenizer::Token t2 = {tokenizer::double_t, "double"};
    tokenizer::Token t3 = {tokenizer::floats, "10.10"};

    std::list<tokenizer::Token> expression;

    expression.push_back(std::move(t1));
    expression.push_back(std::move(t2));
    expression.push_back(std::move(t3));

    Evaluator eval;
    eval.push(expression);

    auto *operand = eval.stackTop();

    CHECK(operand->getType() == Double_t);
    CHECK(operand->toString() == "10.1");
  }


  SUBCASE("assert bad value")
  {
    tokenizer::Token t1 = {tokenizer::push, "push"};
    tokenizer::Token t2 = {tokenizer::double_t, "int8"};
    tokenizer::Token t3 = {tokenizer::floats, "9"};

    tokenizer::Token t4 = {tokenizer::push, "assert"};
    tokenizer::Token t5 = {tokenizer::double_t, "int8"};
    tokenizer::Token t6 = {tokenizer::floats, "10"};

    std::list<tokenizer::Token> push_expr;
    std::list<tokenizer::Token> assert_expr;

    push_expr.push_back(std::move(t1));
    push_expr.push_back(std::move(t2));
    push_expr.push_back(std::move(t3));

    assert_expr.push_back(std::move(t4));
    assert_expr.push_back(std::move(t5));
    assert_expr.push_back(std::move(t6));

    Evaluator eval;
    eval.push(push_expr);

    try
    {
        eval.assert(assert_expr);
    }
    catch(exceptions::Exceptions &err)
    {
       CHECK(err.getType() == exceptions::bad_assert);
    }

  }

  SUBCASE("pop")
  {

    tokenizer::Token t1 = {tokenizer::push, "push"};
    tokenizer::Token t2 = {tokenizer::int8, "int8"};
    tokenizer::Token t3 = {tokenizer::integers, "9"};

    tokenizer::Token t4 = {tokenizer::push, "push"};
    tokenizer::Token t5 = {tokenizer::int16, "int16"};
    tokenizer::Token t6 = {tokenizer::integers, "29"};

    std::list<tokenizer::Token> push_expr;
    std::list<tokenizer::Token> push_expr2;

    push_expr.push_back(std::move(t1));
    push_expr.push_back(std::move(t2));
    push_expr.push_back(std::move(t3));

    push_expr2.push_back(std::move(t4));
    push_expr2.push_back(std::move(t5));
    push_expr2.push_back(std::move(t6));

    Evaluator eval;
    eval.push(push_expr);
    eval.push(push_expr2);

    CHECK(eval.stackTop()->getType() == Int16_t);
    CHECK(eval.stackTop()->toString() == "29");

    eval.pop();

    CHECK(eval.stackTop()->getType() == Int8_t);
    CHECK(eval.stackTop()->toString() == "9");
  }

  SUBCASE("add")
  {
    tokenizer::Token t1 = {tokenizer::push, "push"};
    tokenizer::Token t2 = {tokenizer::int8, "int8"};
    tokenizer::Token t3 = {tokenizer::integers, "9"};

    tokenizer::Token t4 = {tokenizer::push, "push"};
    tokenizer::Token t5 = {tokenizer::int8, "int8"};
    tokenizer::Token t6 = {tokenizer::integers, "29"};

    std::list<tokenizer::Token> push_expr;
    std::list<tokenizer::Token> push_expr2;

    push_expr.push_back(std::move(t1));
    push_expr.push_back(std::move(t2));
    push_expr.push_back(std::move(t3));

    push_expr2.push_back(std::move(t4));
    push_expr2.push_back(std::move(t5));
    push_expr2.push_back(std::move(t6));

    Evaluator eval;
    eval.push(push_expr);
    eval.push(push_expr2);
    eval.add();

    CHECK(eval.stackTop()->getType() == Int8_t);
    CHECK(eval.stackTop()->toString() == "38");
  }

  SUBCASE("add with overflow exception")
  {
    tokenizer::Token t1 = {tokenizer::push, "push"};
    tokenizer::Token t2 = {tokenizer::int8, "int8"};
    tokenizer::Token t3 = {tokenizer::integers, "100"};

    tokenizer::Token t4 = {tokenizer::push, "push"};
    tokenizer::Token t5 = {tokenizer::int8, "int8"};
    tokenizer::Token t6 = {tokenizer::integers, "100"};

    std::list<tokenizer::Token> push_expr;
    std::list<tokenizer::Token> push_expr2;

    push_expr.push_back(std::move(t1));
    push_expr.push_back(std::move(t2));
    push_expr.push_back(std::move(t3));

    push_expr2.push_back(std::move(t4));
    push_expr2.push_back(std::move(t5));
    push_expr2.push_back(std::move(t6));

    Evaluator eval;
    eval.push(push_expr);
    eval.push(push_expr2);
    try
    {
      eval.add();
    }
    catch(exceptions::Exceptions &err)
    {
      CHECK(err.getType() == exceptions::overflow);
    };
  }

  SUBCASE("sub")
  {

    tokenizer::Token t1 = {tokenizer::push, "push"};
    tokenizer::Token t2 = {tokenizer::int8, "int8"};
    tokenizer::Token t3 = {tokenizer::integers, "29"};

    tokenizer::Token t4 = {tokenizer::push, "push"};
    tokenizer::Token t5 = {tokenizer::int8, "int8"};
    tokenizer::Token t6 = {tokenizer::integers, "9"};

    std::list<tokenizer::Token> push_expr;
    std::list<tokenizer::Token> push_expr2;

    push_expr.push_back(std::move(t1));
    push_expr.push_back(std::move(t2));
    push_expr.push_back(std::move(t3));

    push_expr2.push_back(std::move(t4));
    push_expr2.push_back(std::move(t5));
    push_expr2.push_back(std::move(t6));

    Evaluator eval;
    eval.push(push_expr);
    eval.push(push_expr2);
    eval.sub();

    CHECK(eval.stackTop()->getType() == Int8_t);
    CHECK(eval.stackTop()->toString() == "20");
  }

  SUBCASE("div")
  {

    tokenizer::Token t1 = {tokenizer::push, "push"};
    tokenizer::Token t2 = {tokenizer::int8, "int8"};
    tokenizer::Token t3 = {tokenizer::integers, "20"};

    tokenizer::Token t4 = {tokenizer::push, "push"};
    tokenizer::Token t5 = {tokenizer::int8, "int8"};
    tokenizer::Token t6 = {tokenizer::integers, "4"};

    std::list<tokenizer::Token> push_expr;
    std::list<tokenizer::Token> push_expr2;

    push_expr.push_back(std::move(t1));
    push_expr.push_back(std::move(t2));
    push_expr.push_back(std::move(t3));

    push_expr2.push_back(std::move(t4));
    push_expr2.push_back(std::move(t5));
    push_expr2.push_back(std::move(t6));

    Evaluator eval;
    eval.push(push_expr);
    eval.push(push_expr2);
    eval.div();

    CHECK(eval.stackTop()->getType() == Int8_t);
    CHECK(eval.stackTop()->toString() == "5");
  }

 SUBCASE("mul")
  {
    tokenizer::Token t1 = {tokenizer::push, "push"};
    tokenizer::Token t2 = {tokenizer::double_t, "double"};
    tokenizer::Token t3 = {tokenizer::floats, "20.20"};

    tokenizer::Token t4 = {tokenizer::push, "push"};
    tokenizer::Token t5 = {tokenizer::int8, "int8"};
    tokenizer::Token t6 = {tokenizer::integers, "4"};

    std::list<tokenizer::Token> push_expr;
    std::list<tokenizer::Token> push_expr2;

    push_expr.push_back(std::move(t1));
    push_expr.push_back(std::move(t2));
    push_expr.push_back(std::move(t3));

    push_expr2.push_back(std::move(t4));
    push_expr2.push_back(std::move(t5));
    push_expr2.push_back(std::move(t6));

    Evaluator eval;
    eval.push(push_expr);
    eval.push(push_expr2);
    eval.mul();

    CHECK(eval.stackTop()->getType() == Double_t);
    CHECK(eval.stackTop()->toString() == "80.8");
  }

 SUBCASE("mul")
  {
    tokenizer::Token t1 = {tokenizer::push, "push"};
    tokenizer::Token t2 = {tokenizer::int32, "int32"};
    tokenizer::Token t3 = {tokenizer::integers, "10"};

    tokenizer::Token t4 = {tokenizer::push, "push"};
    tokenizer::Token t5 = {tokenizer::int8, "int8"};
    tokenizer::Token t6 = {tokenizer::integers, "3"};

    std::list<tokenizer::Token> push_expr;
    std::list<tokenizer::Token> push_expr2;

    push_expr.push_back(std::move(t1));
    push_expr.push_back(std::move(t2));
    push_expr.push_back(std::move(t3));

    push_expr2.push_back(std::move(t4));
    push_expr2.push_back(std::move(t5));
    push_expr2.push_back(std::move(t6));

    Evaluator eval;
    eval.push(push_expr);
    eval.push(push_expr2);
    eval.mod();

    CHECK(eval.stackTop()->getType() == Int32_t);
    CHECK(eval.stackTop()->toString() == "1");
  }

  SUBCASE("print with assert error")
  {

    tokenizer::Token t1 = {tokenizer::push, "push"};
    tokenizer::Token t2 = {tokenizer::int16, "int16"};
    tokenizer::Token t3 = {tokenizer::integers, "65"};

    std::list<tokenizer::Token> push_expr;

    push_expr.push_back(std::move(t1));
    push_expr.push_back(std::move(t2));
    push_expr.push_back(std::move(t3));

    Evaluator eval;
    eval.push(push_expr);
    try
    {
      /* wrong type */
       eval.print();
    }
    catch(exceptions::Exceptions &err)
    {
      CHECK(err.getType() == exceptions::bad_print_type);
    };

  };
};


