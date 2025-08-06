#ifndef INTERPRETH_H
#define INTERPRETH_H

#include <string>
#include <vector>

// --- Self-Contained Universal Definitions ---
// These definitions are self-contained to ensure no external dependencies are needed.
// They provide the necessary types for the 'interpret' function signature.

// Universal, self-contained node kind enumeration
enum class NodeKind {
    Program,
    Capsule,
    Macro,
    Val,
    Loop,
    Say,
    When,
    Block,
    Op,
    Number,
    String,
    Identifier
};

// Universal, self-contained Abstract Syntax Tree (AST) node structure
struct ASTNode {
    NodeKind kind;
    std::string val;
    std::vector<ASTNode> args;
    std::vector<ASTNode> body;
};

// --- Pure C++ Interpreter Interface ---
// This function declaration is universally compatible and relies only on the
// self-contained types defined above.

void interpret(const ASTNode& ast);

#endif // INTERPRETH_H

