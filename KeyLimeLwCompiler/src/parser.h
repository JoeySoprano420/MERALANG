#pragma once
#include <vector>
#include <string>
#include "lexer.h"

enum class NodeKind { Program, Capsule, Macro, Val, Loop, Say, When, Block, Op, Number, String, Identifier };
struct ASTNode {
    NodeKind kind;
    std::string val;
    std::vector<ASTNode> args;
    std::vector<ASTNode> body;
};
ASTNode parse(const std::vector<Token>& tokens);
