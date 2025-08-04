// src/ir_generator.cpp
#include "parser.h"
#include <sstream>

namespace IRGenerator {
    std::string generate(const std::shared_ptr<ASTNode>& ast) {
        std::ostringstream oss;
        for (auto& child : ast->children) {
            oss << "[IR] " << child->value << "\n";
        }
        return oss.str();
    }
}
