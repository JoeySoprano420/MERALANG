#pragma once
#include <string>
#include <unordered_set>

// Allowed pseudo-opcodes (extend for real NASM/VM set)
inline const std::unordered_set<std::string>& allowed_opcodes() {
    static std::unordered_set<std::string> ops = {
        "mov", "add", "sub", "mul", "div", "jmp", "cmp", "call", "ret", "say", "exit"
    };
    return ops;
}

// Check opcode validity
inline bool verify_opcode(const std::string& op) {
    return allowed_opcodes().count(op) > 0;
}
