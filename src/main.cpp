#define DOCTEST_CONFIG_IMPLEMENT
#include "../include/doctest.h"
#include "../include/program.h"

/* run tests with --test */
int test()
{
 doctest::Context ctx;
 ctx.setOption("abort-after", 5);
 ctx.setOption("no-breaks", true);

 int res = ctx.run();

 if(ctx.shouldExit())
     return res;

  return -1;
}
int main(int ac, char **av)

{
   Program program(ac, av);

   if(program.runTest())
   {
      int res = test();
      if(res > 0)
         return res;
  }
  else
    program.run();
      
  return 0;
}


