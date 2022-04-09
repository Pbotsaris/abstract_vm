#define DOCTEST_CONFIG_IMPLEMENT
#include "../include/doctest.h"
#include "operands.cpp"

int main(void)
{
  doctest::Context ctx;

  ctx.setOption("abort-after", 5);
  ctx.setOption("no-breaks", true);

  int res = ctx.run();

  if(ctx.shouldExit())
      return res;

  return res;
}
