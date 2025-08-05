#include "emitter.h"
std::string emit_nasm(const ASTNode& ast) {
    // Minimal NASM output stub
    std::string out = "section .text\n    global _start\n_start:\n";
    // Walk the AST, outputting NASM for each statement...
    out += "    mov rax, 60\n    xor rdi, rdi\n    syscall\n"; // exit(0)
    return out;
}
