#include <stdexcept>
#include <string>
#include <vector>
#include <map>

// Define NodeKind enum class for AST node types
enum class NodeKind {
    Program, Capsule, Macro, Val, Loop, Say, When, Block, Op, Number, String, Identifier
};

// Define Token struct
struct Token {
    std::string type;
    std::string value;
};

// Define ASTNode struct
struct ASTNode {
    NodeKind kind;
    std::string val;
    std::vector<ASTNode> args;
    std::vector<ASTNode> body;
};

// Example usage: Build AST inline from tokens
int main() {
    // Example tokens vector
    std::vector<Token> tokens;
    tokens.push_back({"macro", "define"});
    tokens.push_back({"val", "x"});
    tokens.push_back({"number", "42"});
    tokens.push_back({"macro", "undef"});

    if (tokens.empty()) {
        throw std::runtime_error("No tokens to parse");
    }

    ASTNode root;
    root.kind = NodeKind::Program;
    root.val = "";

    std::map<std::string, std::vector<ASTNode> > grouped;
    for (size_t i = 0; i < tokens.size(); ++i) {
        const Token& token = tokens[i];
        ASTNode node;
        if (token.type == "capsule") node.kind = NodeKind::Capsule;
        else if (token.type == "macro") node.kind = NodeKind::Macro;
        else if (token.type == "val") node.kind = NodeKind::Val;
        else if (token.type == "loop") node.kind = NodeKind::Loop;
        else if (token.type == "say") node.kind = NodeKind::Say;
        else if (token.type == "when") node.kind = NodeKind::When;
        else if (token.type == "block") node.kind = NodeKind::Block;
        else if (token.type == "op") node.kind = NodeKind::Op;
        else if (token.type == "number") node.kind = NodeKind::Number;
        else if (token.type == "string") node.kind = NodeKind::String;
        else if (token.type == "identifier") node.kind = NodeKind::Identifier;
        else continue;
        node.val = token.value;
        grouped[token.type].push_back(node);
    }

    for (std::map<std::string, std::vector<ASTNode> >::iterator it = grouped.begin(); it != grouped.end(); ++it) {
        ASTNode typeRoot;
        if (it->first == "capsule") typeRoot.kind = NodeKind::Capsule;
        else if (it->first == "macro") typeRoot.kind = NodeKind::Macro;
        else if (it->first == "val") typeRoot.kind = NodeKind::Val;
        else if (it->first == "loop") typeRoot.kind = NodeKind::Loop;
        else if (it->first == "say") typeRoot.kind = NodeKind::Say;
        else if (it->first == "when") typeRoot.kind = NodeKind::When;
        else if (it->first == "block") typeRoot.kind = NodeKind::Block;
        else if (it->first == "op") typeRoot.kind = NodeKind::Op;
        else if (it->first == "number") typeRoot.kind = NodeKind::Number;
        else if (it->first == "string") typeRoot.kind = NodeKind::String;
        else if (it->first == "identifier") typeRoot.kind = NodeKind::Identifier;
        else continue;
        typeRoot.val = "";
        typeRoot.body = it->second;
        root.body.push_back(typeRoot);
    }

    // The AST is now in 'root'
    return 0;
}
