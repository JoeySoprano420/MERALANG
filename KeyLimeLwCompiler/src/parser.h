#pragma once
#include <vector>
#include <string>

#include "../../../AppData/Local/Temp/tgsccfog..h"

// Ensure "lexer.h" is in your project's include directories or the same folder as "parser.h".
// If "lexer.h" is in a subfolder (e.g., "include/lexer.h"), update the include path accordingly:
// #include "include/lexer.h"

enum class NodeKind {
    Program, Capsule, Macro, Val, Loop, Say, When, Block, Op, Number, String, Identifier
};

struct ASTNode {
    NodeKind kind;
    std::string val;
    std::vector<ASTNode> args;
    std::vector<ASTNode> body;
};


