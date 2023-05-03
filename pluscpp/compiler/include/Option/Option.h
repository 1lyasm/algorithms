#ifndef OPTION_H
#define OPTION_H

#include <string>
#include <vector>
#include "Option/ArgVerifier.h"

class Option
{
  std::vector<std::string> Args;
  int ArgCount;

public:
  Option(int argc, char **argv);
  std::string getFileName();
};

#endif
