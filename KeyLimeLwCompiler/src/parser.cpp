#include "parser.h"

static size_t i = 0;
static const std::vector<Token>* ptoks;

// Helper macros
#define CUR (*ptoks)[i]
#define NEXT() (++i < ptoks->size() ? (*ptoks)[i] : Token{TokenType::EndOfFile,"",0})

ASTNode parse_block(); // forward

ASTNode parse_val() {
    ASTNode n{NodeKind::Val};
    ++i; // skip 'val'
    if (CUR.type == TokenType::Identifier) n.val = CUR.lexeme;
    ++i;
    if (CUR.lexeme == "=") ++i;
    if (CUR.type == TokenType::Number) {
        n.args.push_back(ASTNode{NodeKind::Number, CUR.lexeme});
        ++i;
    }
    return n;
}
ASTNode parse_say() {
    ASTNode n{NodeKind::Say};
    ++i;
    if (CUR.type == TokenType::String)
        n.args.push_back(ASTNode{NodeKind::String, CUR.lexeme});
    ++i;
    return n;
}
ASTNode parse_loop() {
    ASTNode n{NodeKind::Loop};
    ++i; // skip loop
    if (CUR.type == TokenType::Identifier)
        n.val = CUR.lexeme;
    ++i; // 'from'
    if (CUR.type == TokenType::Keyword && CUR.lexeme == "from") ++i;
    if (CUR.type == TokenType::Number)
        n.args.push_back(ASTNode{NodeKind::Number, CUR.lexeme});
    ++i; // ':'
    if (CUR.lexeme == ":") ++i;
    n.body.push_back(parse_block());
    return n;
}
ASTNode parse_block() {
    ASTNode n{NodeKind::Block};
    while (i < ptoks->size()) {
        if (CUR.type == TokenType::Keyword && CUR.lexeme == "end") { ++i; break; }
        if (CUR.type == TokenType::Keyword && CUR.lexeme == "val") n.body.push_back(parse_val());
        else if (CUR.type == TokenType::Keyword && CUR.lexeme == "say") n.body.push_back(parse_say());
        else if (CUR.type == TokenType::Keyword && CUR.lexeme == "loop") n.body.push_back(parse_loop());
        else ++i;
    }
    return n;
}
ASTNode parse(const std::vector<Token>& tokens) {
    i = 0; ptoks = &tokens;
    ASTNode root{NodeKind::Program};
    while (i < tokens.size()) {
        if (CUR.type == TokenType::Keyword && CUR.lexeme == "capsule") {
            ASTNode n{NodeKind::Capsule};
            ++i;
            if (CUR.type == TokenType::Identifier) { n.val = CUR.lexeme; ++i; }
            if (CUR.lexeme == ":") ++i;
            n.body.push_back(parse_block());
            root.body.push_back(n);
        }
        else ++i;
    }
    return root;
}
