// src/parser.h
#pragma once
#include "lexer.h"
#include <memory>

struct ASTNode {
    std::string type;
    std::string value;
    std::vector<std::shared_ptr<ASTNode>> children;
};

class Parser {
public:
    static std::shared_ptr<ASTNode> parse(const std::vector<Token>& tokens);
};
