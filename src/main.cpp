#include "operands.cpp"



int main(void)
{
 IOperand<int16_t> int16 = IOperand<int16_t>(10);
 IOperand<int16_t> int16_2 = IOperand<int16_t>(30);
  //
  auto *res = int16 + int16_2;


 std::cout << res->getValue() << '\n';
// std::cout << res.getValue() << '\n';
  //
  //

  delete res;

return 0;
}
