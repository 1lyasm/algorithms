#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <optional>
#include <Lex/TokenType.h>

class Token
{
  std::optional<std::string> Val;
  TokenType Type;

public:
  std::optional<std::string> getVal();
  TokenType getType();
};

#endif
