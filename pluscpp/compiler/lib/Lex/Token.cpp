#include "Lex/Token.h"

std::optional<std::string> Token::getVal()
{
  return Val;
}

TokenType Token::getType()
{
  return Type;
}
