#ifndef PROGRAM_H
#define PROGRAM_H
#include <tuple>
#include <string>
#include "../include/cli.h"

#define TEST_ARGUMENT "--test"

class Program
{
    private:

    struct                  Private;
    CLI                     m_cli;
    bool                    m_test;
    std::string             m_path;

    
  public:
     Program(int ac, char **av);

     int run();
     bool runTest();
};




#endif
