#include "interpreter.h"
#include "emitter.h"
#include "hexvm.h"
#include "dg.h"
#include <iostream>
#include <iomanip>
#include "opcodes.h"

void interpret(const ASTNode& ast) {
    EmitResult er = emit_full(ast);
    std::cout << "[KeyLime LW] --- DG Trace: " << er.dg_trace.dump() << "\n";
    std::cout << "[KeyLime LW] --- HEX IR ---\n";
    for (const auto& line : er.hex_ir) {
        std::string op = line.substr(0, line.find(' '));
        bool legal = verify_opcode(op);
        std::cout << (legal ? "[OK] " : "[!!] ") << line << "\n";
    }
    std::cout << "[KeyLime LW] --- Running on HexVM ---\n";
    std::vector<HexInstr> prog;
    for (const auto& line : er.hex_ir) {
        size_t pos = line.find(' ');
        std::string op = line.substr(0, pos);
        std::string arg = (pos != std::string::npos) ? line.substr(pos+1) : "";
        prog.push_back({op, {arg}});
    }
    HexVM vm;
    vm.exec(prog);
}
