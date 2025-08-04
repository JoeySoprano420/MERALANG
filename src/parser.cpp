// src/parser.cpp
#include "parser.h"
#include <stdexcept>

static size_t pos = 0;
static std::vector<Token> toks;

std::shared_ptr<ASTNode> parseStatement();

std::shared_ptr<ASTNode> Parser::parse(const std::vector<Token>& tokens) {
    toks = tokens;
    pos = 0;
    auto root = std::make_shared<ASTNode>();
    root->type = "Program";
    while (toks[pos].type != TokenType::EndOfFile) {
        root->children.push_back(parseStatement());
    }
    return root;
}

std::shared_ptr<ASTNode> parseStatement() {
    const Token& tok = toks[pos++];
    auto node = std::make_shared<ASTNode>();
    node->type = "Statement";
    node->value = tok.lexeme;
    return node;
}
