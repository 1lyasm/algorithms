#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

#include <string>

class Diagnostic
{
public:
  [[noreturn]] static void error(std::string ErrorOwner, std::string ErrorMsg);
};

#endif
