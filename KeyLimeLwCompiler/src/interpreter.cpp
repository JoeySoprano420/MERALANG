#include "interpreter.h"
#include <iostream>
#include <string>
#include <vector>

// --- Self-Contained Universal Definitions ---
// These definitions are added to fix errors and make the file self-contained.

enum class NodeKind {
    Program, Capsule, Macro, Val, Loop, Say, When, Block, Op, Number, String, Identifier
};

struct ASTNode {
    NodeKind kind;
    std::string val;
    std::vector<ASTNode> args;
    std::vector<ASTNode> body;
};

// Universal, self-contained dependency graph trace object
struct UniversalDGTrace {
    std::string dump() const {
        // Return a neutral, universally valid string representation
        return "{\"nodes\": 0, \"edges\": 0}";
    }
};

// Universal, self-contained result from the code emitter
struct UniversalEmitResult {
    UniversalDGTrace dg_trace;
    std::vector<std::string> hex_ir;
};

// Universal, self-contained instruction for the virtual machine
struct UniversalHexInstr {
    std::string opcode;
    std::vector<std::string> args;
};

// Universal, self-contained virtual machine
class UniversalHexVM {
public:
    void exec(const std::vector<UniversalHexInstr>& program) {
        std::cout << "[HexVM] Executing " << program.size() << " instructions." << std::endl;
        for (std::size_t i = 0; i < program.size(); ++i) {
            const UniversalHexInstr& instr = program[i];
            if (instr.opcode == "say") {
                if (!instr.args.empty()) {
                    std::cout << instr.args[0] << std::endl;
                }
            }
            // Other opcodes can be handled here.
        }
        std::cout << "[HexVM] Execution finished." << std::endl;
    }
};

// Universal, self-contained opcode verification function
bool universal_verify_opcode(const std::string& op) {
    const char* const allowed[] = {"mov", "add", "sub", "mul", "div", "jmp", "cmp", "call", "ret", "say", "exit"};
    for (std::size_t i = 0; i < sizeof(allowed) / sizeof(allowed[0]); ++i) {
        if (op == allowed[i]) {
            return true;
        }
    }
    return false;
}

// Universal, self-contained code emitter function
UniversalEmitResult universal_emit_full(const ASTNode& ast) {
    UniversalEmitResult er;
    // This is a stub. A real implementation would traverse the AST.
    // For demonstration, we create a simple program.
    if (ast.kind == NodeKind::Program) {
        er.hex_ir.push_back("say \"Hello from Universal Interpreter!\"");
        er.hex_ir.push_back("exit");
    }
    return er;
}


// --- Pure C++ Interpreter Implementation ---
// This function is written in pure, fundamental C++ for maximum portability.
// It uses only the self-contained universal types and functions defined above.

void interpret(const ASTNode& ast) {
    // 1. Emit code from the Abstract Syntax Tree
    UniversalEmitResult er = universal_emit_full(ast);

    // 2. Print diagnostic information
    std::cout << "[KeyLime LW] --- DG Trace: " << er.dg_trace.dump() << "\n";
    std::cout << "[KeyLime LW] --- HEX IR ---\n";
    for (std::size_t i = 0; i < er.hex_ir.size(); ++i) {
        const std::string& line = er.hex_ir[i];
        std::size_t space_pos = line.find(' ');
        std::string op = line.substr(0, space_pos);
        bool is_legal = universal_verify_opcode(op);
        std::cout << (is_legal ? "[OK] " : "[!!] ") << line << "\n";
    }

    // 3. Prepare the program for the virtual machine
    std::cout << "[KeyLime LW] --- Running on HexVM ---\n";
    std::vector<UniversalHexInstr> program;
    for (std::size_t i = 0; i < er.hex_ir.size(); ++i) {
        const std::string& line = er.hex_ir[i];
        std::size_t space_pos = line.find(' ');
        UniversalHexInstr instr;
        instr.opcode = line.substr(0, space_pos);
        if (space_pos != std::string::npos) {
            instr.args.push_back(line.substr(space_pos + 1));
        }
        program.push_back(instr);
    }

    // 4. Execute the program
    UniversalHexVM vm;
    vm.exec(program);
}
