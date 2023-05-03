#include "Option/ArgVerifier.h"
#include "Diagnostic/Diagnostic.h"
#include <regex>

void ArgVerifier::verify(int ArgCount, std::vector<std::string> Args)
{
  std::string ErrorOwner = "compiler";
  verifyArgCount(ArgCount, ErrorOwner);
  verifyFileName(Args[1], ErrorOwner);
}

void ArgVerifier::verifyArgCount(int ArgCount, std::string ErrorOwner)
{
  if (ArgCount == 1)
  {
    Diagnostic::error(ErrorOwner, "no input files");
  }
  if (ArgCount != 2)
  {
    Diagnostic::error(ErrorOwner, "too many arguments");
  }
}

void ArgVerifier::verifyFileName(std::string FileName, std::string ErrorOwner)
{
  std::regex FileNameRegex(".+\\.cpp");
  std::smatch Match;
  if (std::regex_match(FileName, Match, FileNameRegex) == 0)
  {
    Diagnostic::error(ErrorOwner, "invalid file name");
  }
}
