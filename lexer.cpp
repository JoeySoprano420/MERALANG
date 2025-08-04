// src/lexer.cpp
#include "lexer.h"
#include <fstream>
#include <cctype>

std::vector<Token> Lexer::tokenizeFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Token> tokens;
    std::string line;
    int lineNum = 1;

    while (std::getline(file, line)) {
        int col = 1;
        for (size_t i = 0; i < line.length(); ++i, ++col) {
            char c = line[i];
            if (isspace(c)) continue;
            else if (isalpha(c)) {
                std::string ident;
                while (isalnum(line[i])) ident += line[i++];
                --i;
                tokens.push_back({TokenType::Identifier, ident, lineNum, col});
            } else if (isdigit(c)) {
                std::string num;
                while (isdigit(line[i])) num += line[i++];
                --i;
                tokens.push_back({TokenType::Number, num, lineNum, col});
            } else if (c == '"') {
                std::string str;
                ++i;
                while (line[i] != '"') str += line[i++];
                tokens.push_back({TokenType::String, str, lineNum, col});
            } else {
                tokens.push_back({TokenType::Symbol, std::string(1, c), lineNum, col});
            }
        }
        ++lineNum;
    }
    tokens.push_back({TokenType::EndOfFile, "", lineNum, 0});
    return tokens;
}
