// src/llvm_bridge.cpp
#include "parser.h"
#include <sstream>

namespace LLVMBridge {
    std::string generateLLVM(const std::string& ir) {
        std::ostringstream oss;
        oss << "; ModuleID = 'meralang'\n";
        oss << "define i32 @main() {\n";
        oss << "entry:\n";
        oss << "    ; from IR\n";
        oss << "    ; " << ir;
        oss << "    ret i32 0\n";
        oss << "}\n";
        return oss.str();
    }
}
