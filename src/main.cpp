#define DOCTEST_CONFIG_IMPLEMENT
#include "../include/doctest.h"
#include "../include/IOperand.h"

int main(void)
{
  doctest::Context ctx;

  ctx.setOption("abort-after", 5);
  ctx.setOption("no-breaks", true);

  int res = ctx.run();

  if(ctx.shouldExit())
      return res;

 //   auto n = IOperand<int8_t>(8);

  return res;
}
