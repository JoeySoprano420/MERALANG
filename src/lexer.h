// src/lexer.h
#pragma once
#include <string>
#include <vector>

enum class TokenType {
    Keyword, Identifier, Number, String, Operator, Symbol, EndOfFile
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;
};

class Lexer {
public:
    static std::vector<Token> tokenizeFile(const std::string& filename);
};
