#include "../include/program.h"

struct Program::Private
{
    static bool hasPath(Program &self) {return self.m_path.length() != 0; };

   };

Program::Program(int ac, char **av)
: m_test(false), m_path("")
{ 

   for(int i = 1; i < ac; i++)
    {

      std::string arg = av[i];

      if(arg == TEST_ARGUMENT)
          m_test = true;

       else if(!Private::hasPath(*this))
          m_path = std::move(arg);

    };
} 

int Program::run()
{
    if(!Private::hasPath(*this))
          m_cli.mainLoop();

    return 0;
};


bool Program::runTest() {return m_test; };


