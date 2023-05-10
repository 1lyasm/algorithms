#include "Diagnostic/Diagnostic.h"

#include <iostream>
#include <cstdlib>

[[noreturn]] void Diagnostic::error(std::string ErrorOwner, std::string ErrorMsg)
{
  std::cout << ErrorOwner << ": error: " << ErrorMsg << "\n";
  std::exit(EXIT_FAILURE);
}
