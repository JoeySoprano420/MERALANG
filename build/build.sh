#!/bin/bash
set -e

# Detect platform
ARCH=$(uname -m)
if [[ "$ARCH" == "x86_64" ]]; then
    ENABLE_DLMT_FASTPATH=ON
    ENABLE_SYMBOLIC_TRACE=ON
else
    ENABLE_DLMT_FASTPATH=OFF
    ENABLE_SYMBOLIC_TRACE=OFF
fi

# LLVM detection
if command -v llvm-config &> /dev/null; then
    ENABLE_LLVM=ON
else
    ENABLE_LLVM=OFF
fi

# Configure build
mkdir -p build
cd build
cmake .. -G "Unix Makefiles" \
    -DENABLE_LLVM=$ENABLE_LLVM \
    -DENABLE_SAN2NASM=ON \
    -DENABLE_DEBUGGER=ON \
    -DENABLE_OPTIMIZER=ON \
    -DENABLE_SYMBOLIC_TRACE=$ENABLE_SYMBOLIC_TRACE \
    -DENABLE_DLMT_FASTPATH=$ENABLE_DLMT_FASTPATH

# Build
cmake --build . --target meralang repl_ui test_capsules
