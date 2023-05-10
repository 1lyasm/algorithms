#include "Driver/Driver.h"
#include <iostream>
#include <vector>
#include "Option/Option.h"
#include "Lex/Lex.h"

int main(int argc, char **argv)
{
  Option option(argc, argv);
  Lex::getTokens(option.getFileName());
  return 0;
}
