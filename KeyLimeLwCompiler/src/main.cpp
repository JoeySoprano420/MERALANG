#include <iostream>
#include <fstream>
#include <string>
#include "lexer.h"
#include "parser.h"
#include "emitter.h"
#include "interpreter.h"

void show_usage() {
    std::cout << "KeyLime LW (MeraLang Lite Compiler)\n"
              << "Usage: keylime-lw <file.mera> [--emit-nasm|--run]\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) { show_usage(); return 1; }
    std::string file = argv[1];

    std::ifstream in(file);
    if (!in) { std::cerr << "Cannot open: " << file << "\n"; return 2; }
    std::string src((std::istreambuf_iterator<char>(in)), {});

    auto tokens = lex(src);
    auto ast = parse(tokens);

    if (argc > 2 && std::string(argv[2]) == "--emit-nasm") {
        auto er = emit_full(ast);
        std::ofstream out("output.asm");
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
