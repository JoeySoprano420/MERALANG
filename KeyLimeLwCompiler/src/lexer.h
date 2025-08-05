#pragma once
#include <string>
#include <vector>

enum class TokenType { Identifier, Number, String, Keyword, Symbol, Newline, EndOfFile };
struct Token { TokenType type; std::string lexeme; int line; };
std::vector<Token> lex(const std::string& src);
