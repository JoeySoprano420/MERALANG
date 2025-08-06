#pragma once
#include <string>
#include <vector>

// Universal, self-contained opcode set
class Opcodes {
public:
    Opcodes() {
        ops.push_back("mov");
        ops.push_back("add");
        ops.push_back("sub");
        ops.push_back("mul");
        ops.push_back("div");
        ops.push_back("jmp");
        ops.push_back("cmp");
        ops.push_back("call");
        ops.push_back("ret");
        ops.push_back("say");
        ops.push_back("exit");
    }

    bool verify(const std::string& op) const {
        for (size_t i = 0; i < ops.size(); ++i) {
            if (ops[i] == op) return true;
        }
        return false;
    }

    const std::vector<std::string>& allowed() const {
        return ops;
    }

private:
    std::vector<std::string> ops;
};
