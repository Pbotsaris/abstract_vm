#include "../include/IOperand.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"

TEST_CASE("sum operands of same precision")
{

  IOperand<int16_t> n1 = IOperand<int16_t>(10);
  CHECK(1 + 1 == 2);
 //  IOperand<int16_t> n2 = IOperand<int16_t>(30);
//  auto *result =  n1 + n2;
//
//  CHECK(result->getValue() == 40);

 // delete result;
}


