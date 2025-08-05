#include "parser.h"

ASTNode parse(const std::vector<Token>& tokens) {
    size_t i = 0;
    ASTNode root { "program" };
    while (i < tokens.size()) {
        if (tokens[i].type == TokenType::Keyword && tokens[i].lexeme == "capsule") {
            ASTNode node{ "capsule" };
            ++i;
            if (tokens[i].type == TokenType::Identifier)
                node.args.push_back(tokens[i++].lexeme);
            root.body.push_back(node);
        }
        ++i;
    }
    return root;
}
