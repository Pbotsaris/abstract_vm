#define DOCTEST_CONFIG_IMPLEMENT
#include "../include/doctest.h"
#include "operands.cpp"

double round_up(double value, int decimal_places) {
  const double multiplier = std::pow(10.0, decimal_places);
  return std::ceil(value * multiplier) / multiplier;
}

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
