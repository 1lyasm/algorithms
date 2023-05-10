#ifndef LEX_H
#define LEX_H

#include <string>
#include <optional>
#include <vector>
#include "Lex/Token.h"
#include "Lex/TokenType.h"

class Lex
{
public:
  static std::vector<Token> getTokens(std::string FileName);
};

#endif
