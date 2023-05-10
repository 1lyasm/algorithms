#include "Option/Option.h"
#include <iostream>
#include <cstdlib>
#include <regex>

Option::Option(int argc, char **argv)
{
  ArgCount = argc;
  for (int i = 0; i < ArgCount; ++i)
  {
    Args.push_back(std::string(argv[i]));
  }
  ArgVerifier::verify(ArgCount, Args);
}

std::string Option::getFileName()
{
  return Args[1];
}
