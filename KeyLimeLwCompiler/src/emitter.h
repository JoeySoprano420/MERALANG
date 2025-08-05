#pragma once
#include "parser.h"
#include <string>
#include <vector>
#include "opcodes.h"
#include "dg.h"

struct EmitResult {
    std::string nasm;
    std::vector<std::string> hex_ir;
    DGState dg_trace;
};
EmitResult emit_full(const ASTNode& ast);
