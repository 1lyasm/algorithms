#ifndef ARG_VERIFIER_H
#define ARG_VERIFIER_H

#include <vector>
#include <string>

class ArgVerifier
{
  static void verifyArgCount(int ArgCount, std::string ErrorOwner);
  static void verifyFileName(std::string FileName, std::string ErrorOwner);

public:
  static void verify(int ArgCount, std::vector<std::string> Args);
};

#endif
