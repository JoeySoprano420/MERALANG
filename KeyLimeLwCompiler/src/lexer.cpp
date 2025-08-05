#include "lexer.h"
#include <cctype>

std::vector<Token> lex(const std::string& src) {
    std::vector<Token> tokens;
    int line = 1;
    size_t i = 0;
    while (i < src.size()) {
        if (isspace(src[i])) {
            if (src[i] == '\n') ++line;
            ++i; continue;
        }
        if (isalpha(src[i])) {
            size_t start = i;
            while (isalnum(src[i]) || src[i] == '_') ++i;
            std::string lex = src.substr(start, i - start);
            TokenType type = (lex == "macro" || lex == "capsule" || lex == "val" || lex == "loop" || lex == "say" || lex == "end") ? TokenType::Keyword : TokenType::Identifier;
            tokens.push_back({ type, lex, line });
            continue;
        }
        if (isdigit(src[i])) {
            size_t start = i;
            while (isdigit(src[i])) ++i;
            tokens.push_back({ TokenType::Number, src.substr(start, i - start), line });
            continue;
        }
        if (src[i] == '"') {
            size_t start = ++i;
            while (src[i] && src[i] != '"') ++i;
            tokens.push_back({ TokenType::String, src.substr(start, i - start), line });
            ++i;
            continue;
        }
        if (std::string("(){}:,=+-*/").find(src[i]) != std::string::npos) {
            tokens.push_back({ TokenType::Symbol, std::string(1, src[i]), line });
            ++i; continue;
        }
        ++i;
    }
    tokens.push_back({ TokenType::EndOfFile, "", line });
    return tokens;
}
