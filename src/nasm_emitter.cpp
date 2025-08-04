// src/nasm_emitter.cpp
#include "parser.h"
#include <sstream>

namespace NASMEmitter {
    std::string emit(const std::string& ir) {
        std::ostringstream out;
        out << "section .text\n_start:\n";
        out << "    ; emitted from IR\n";
        out << "    ; " << ir;
        out << "    mov eax, 60\n    xor edi, edi\n    syscall\n";
        return out.str();
    }
}
