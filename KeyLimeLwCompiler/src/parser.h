#pragma once
#include <vector>
#include <string>
#include "lexer.h"

struct ASTNode {
    std::string type;
    std::vector<std::string> args;
    std::vector<ASTNode> body;
};
ASTNode parse(const std::vector<Token>& tokens);
