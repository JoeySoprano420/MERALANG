#include "emitter.h"
#include <sstream>
#include <iomanip>

static void emit_block(const ASTNode& n, std::ostringstream& nasm, std::vector<std::string>& hex, DGState& dg, int& val) {
    for (const auto& c : n.body) {
        if (c.kind == NodeKind::Val && !c.args.empty()) {
            int x = std::stoi(c.args[0].val);
            val = x; dg.push(x);
            nasm << "    mov rax, " << x << "\n";
            hex.push_back("mov " + std::to_string(x));
        }
        else if (c.kind == NodeKind::Say && !c.args.empty()) {
            nasm << "    ; say \"" << c.args[0].val << "\"\n";
            hex.push_back("say \"" + c.args[0].val + "\"");
        }
        else if (c.kind == NodeKind::Loop && !c.args.empty()) {
            int from = std::stoi(c.args[0].val);
            nasm << "    ; loop " << c.val << " from " << from << "\n";
            hex.push_back("mov 0");
            for (int i = from; i <= from+2; ++i) {
                dg.push(i);
                nasm << "    ; step " << i << "\n";
                hex.push_back("say \"Blur step " + std::to_string(i) + "\"");
            }
        }
    }
}

EmitResult emit_full(const ASTNode& ast) {
    EmitResult out;
    std::ostringstream nasm;
    int val = 0;
    DGState dg;
    std::vector<std::string> hex_ir;

    nasm << "section .text\n    global _start\n_start:\n";
    for (const auto& n : ast.body)
        emit_block(n.body[0], nasm, hex_ir, dg, val);
    nasm << "    mov rax, 60\n    xor rdi, rdi\n    syscall\n"; // exit(0)
    out.nasm = nasm.str();
    out.hex_ir = hex_ir;
    out.dg_trace = dg;
    return out;
}
