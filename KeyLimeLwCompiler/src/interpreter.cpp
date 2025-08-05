#include "interpreter.h"
#include <iostream>
void interpret(const ASTNode& ast) {
    std::cout << "[KeyLime LW]: Running capsule...\n";
    for (const auto& n : ast.body)
        std::cout << "Capsule: " << (n.args.empty() ? "(unnamed)" : n.args[0]) << "\n";
}
