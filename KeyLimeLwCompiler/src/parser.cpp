#include <string>
#include <vector>
#include <stdexcept>

// Universal, self-contained AST types
enum class NodeKind {
    Program, Capsule, Macro, Val, Loop, Say, When, Block, Op, Number, String, Identifier
};

struct ASTNode {
    NodeKind kind;
    std::string val;
    std::vector<ASTNode> args;
    std::vector<ASTNode> body;
};

// Universal token type
enum class TokenType {
    Keyword, Identifier, Number, String, EndOfFile
};

struct Token {
    TokenType type;
    std::string lexeme;
};

// Pure, portable parser implementation
namespace {

ASTNode parse_val(const std::vector<Token>& tokens, size_t& i) {
    ASTNode n;
    n.kind = NodeKind::Val;
    ++i;
    if (i < tokens.size() && tokens[i].type == TokenType::Identifier)
        n.val = tokens[i].lexeme;
    ++i;
    if (i < tokens.size() && tokens[i].lexeme == "=") ++i;
    if (i < tokens.size() && tokens[i].type == TokenType::Number) {
        ASTNode num;
        num.kind = NodeKind::Number;
        num.val = tokens[i].lexeme;
        n.args.push_back(num);
        ++i;
    }
    return n;
}

ASTNode parse_say(const std::vector<Token>& tokens, size_t& i) {
    ASTNode n;
    n.kind = NodeKind::Say;
    ++i;
    if (i < tokens.size() && tokens[i].type == TokenType::String) {
        ASTNode str;
        str.kind = NodeKind::String;
        str.val = tokens[i].lexeme;
        n.args.push_back(str);
    }
    ++i;
    return n;
}

ASTNode parse_loop(const std::vector<Token>& tokens, size_t& i);
ASTNode parse_block(const std::vector<Token>& tokens, size_t& i);

ASTNode parse_loop(const std::vector<Token>& tokens, size_t& i) {
    ASTNode n;
    n.kind = NodeKind::Loop;
    ++i;
    if (i < tokens.size() && tokens[i].type == TokenType::Identifier)
        n.val = tokens[i].lexeme;
    ++i;
    if (i < tokens.size() && tokens[i].type == TokenType::Keyword && tokens[i].lexeme == "from") ++i;
    if (i < tokens.size() && tokens[i].type == TokenType::Number) {
        ASTNode num;
        num.kind = NodeKind::Number;
        num.val = tokens[i].lexeme;
        n.args.push_back(num);
    }
    ++i;
    if (i < tokens.size() && tokens[i].lexeme == ":") ++i;
    n.body.push_back(parse_block(tokens, i));
    return n;
}

ASTNode parse_block(const std::vector<Token>& tokens, size_t& i) {
    ASTNode n;
    n.kind = NodeKind::Block;
    while (i < tokens.size()) {
        if (tokens[i].type == TokenType::Keyword && tokens[i].lexeme == "end") { ++i; break; }
        if (tokens[i].type == TokenType::Keyword && tokens[i].lexeme == "val")
            n.body.push_back(parse_val(tokens, i));
        else if (tokens[i].type == TokenType::Keyword && tokens[i].lexeme == "say")
            n.body.push_back(parse_say(tokens, i));
        else if (tokens[i].type == TokenType::Keyword && tokens[i].lexeme == "loop")
            n.body.push_back(parse_loop(tokens, i));
        else ++i;
    }
    return n;
}

} // anonymous namespace

ASTNode parse(const std::vector<Token>& tokens) {
    size_t i = 0;
    ASTNode root;
    root.kind = NodeKind::Program;
    while (i < tokens.size()) {
        if (tokens[i].type == TokenType::Keyword && tokens[i].lexeme == "capsule") {
            ASTNode n;
            n.kind = NodeKind::Capsule;
            ++i;
            if (i < tokens.size() && tokens[i].type == TokenType::Identifier) {
                n.val = tokens[i].lexeme;
                ++i;
            }
            if (i < tokens.size() && tokens[i].lexeme == ":") ++i;
            n.body.push_back(parse_block(tokens, i));
            root.body.push_back(n);
        } else {
            ++i;
        }
    }
    return root;
}
