#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

struct HexInstr {
    std::string opcode;
    std::vector<std::string> args;
};

class HexVM {
    int reg[8]{};
    bool running = true;
public:
    void exec(const std::vector<HexInstr>& prog) {
        size_t ip = 0;
        running = true;
        while (ip < prog.size() && running) {
            const auto& ins = prog[ip];
            if      (ins.opcode == "say" && !ins.args.empty()) std::cout << ins.args[0] << "\n";
            else if (ins.opcode == "exit") running = false;
            else if (ins.opcode == "add") reg[0] += std::stoi(ins.args[0]);
            else if (ins.opcode == "sub") reg[0] -= std::stoi(ins.args[0]);
            ++ip;
        }
    }
};
