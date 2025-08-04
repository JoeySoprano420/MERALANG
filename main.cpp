// src/main.cpp
#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "ir_generator.h"
#include "nasm_emitter.h"
#include "llvm_bridge.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: meralang <source.mera>\n";
        return 1;
    }

    std::string filePath = argv[1];
    auto tokens = Lexer::tokenizeFile(filePath);
    auto ast = Parser::parse(tokens);
    auto ir = IRGenerator::generate(ast);

    std::cout << "[NASM]\n";
    std::cout << NASMEmitter::emit(ir);

    std::cout << "\n[LLVM IR]\n";
    std::cout << LLVMBridge::generateLLVM(ir);

    return 0;
}
