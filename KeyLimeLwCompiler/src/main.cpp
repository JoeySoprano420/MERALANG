#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Universal, self-contained token, AST, and stub interfaces
enum class TokenType { Keyword, Identifier, Number, String, EndOfFile };
struct Token { TokenType type; std::string lexeme; };

enum class NodeKind { Program, Capsule, Macro, Val, Loop, Say, When, Block, Op, Number, String, Identifier };
struct ASTNode {
    NodeKind kind;
    std::string val;
    std::vector<ASTNode> args;
    std::vector<ASTNode> body;
};

// Stub lexer: splits by whitespace, for demonstration only
std::vector<Token> lex(const std::string& src) {
    std::vector<Token> tokens;
    size_t pos = 0, len = src.size();
    while (pos < len) {
        while (pos < len && std::isspace(static_cast<unsigned char>(src[pos]))) ++pos;
        if (pos >= len) break;
        size_t start = pos;
        while (pos < len && !std::isspace(static_cast<unsigned char>(src[pos]))) ++pos;
        std::string word = src.substr(start, pos - start);
        if (word == "val" || word == "say" || word == "loop" || word == "capsule")
            tokens.push_back({ TokenType::Keyword, word });
        else if (!word.empty() && std::isdigit(static_cast<unsigned char>(word[0])))
            tokens.push_back({ TokenType::Number, word });
        else if (!word.empty())
            tokens.push_back({ TokenType::Identifier, word });
    }
    tokens.push_back({ TokenType::EndOfFile, "" });
    return tokens;
}

// Stub parser: creates a root node with all tokens as children
ASTNode parse(const std::vector<Token>& tokens) {
    ASTNode root;
    root.kind = NodeKind::Program;
    for (size_t i = 0; i < tokens.size(); ++i) {
        ASTNode n;
        if (tokens[i].type == TokenType::Keyword) n.kind = NodeKind::Val;
        else if (tokens[i].type == TokenType::Number) n.kind = NodeKind::Number;
        else if (tokens[i].type == TokenType::Identifier) n.kind = NodeKind::Identifier;
        else continue;
        n.val = tokens[i].lexeme;
        root.body.push_back(n);
    }
    return root;
}

// Stub emitter: outputs a string representation
struct EmitResult { std::string nasm; };
EmitResult emit_full(const ASTNode& ast) {
    std::string out = "; NASM output\n";
    for (size_t i = 0; i < ast.body.size(); ++i) {
        out += "; " + ast.body[i].val + "\n";
    }
    return { out };
}

// Stub interpreter: prints AST node values
void interpret(const ASTNode& ast) {
    for (size_t i = 0; i < ast.body.size(); ++i) {
        std::cout << "Run: " << ast.body[i].val << std::endl;
    }
}

void show_usage() {
    std::cout << "KeyLime LW (MeraLang Lite Compiler)\n"
        << "Usage: keylime-lw <file.mera> [--emit-nasm|--run]\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) { show_usage(); return 1; }
    std::string file = argv[1];

    std::ifstream in(file.c_str(), std::ios::in | std::ios::binary);
    if (!in) { std::cerr << "Cannot open: " << file << "\n"; return 2; }
    std::string src;
    in.seekg(0, std::ios::end);
    src.resize(static_cast<size_t>(in.tellg()));
    in.seekg(0, std::ios::beg);
    in.read(&src[0], src.size());

    std::vector<Token> tokens = lex(src);
    ASTNode ast = parse(tokens);

    if (argc > 2 && std::string(argv[2]) == "--emit-nasm") {
        EmitResult er = emit_full(ast);
        std::ofstream out("output.asm", std::ios::out | std::ios::binary);
        out << er.nasm;
        std::cout << "NASM written to output.asm\n";
        return 0;
    }
    if (argc > 2 && std::string(argv[2]) == "--run") {
        interpret(ast);
        return 0;
    }

    show_usage();
    return 0;
}
