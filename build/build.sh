#!/bin/bash
set -e

ARCH=$(uname -m)
if [[ "$ARCH" == "x86_64" ]]; then
    ENABLE_DLMT_FASTPATH=ON
    ENABLE_SYMBOLIC_TRACE=ON
else
    ENABLE_DLMT_FASTPATH=OFF
    ENABLE_SYMBOLIC_TRACE=OFF
fi

if command -v llvm-config &> /dev/null; then
    ENABLE_LLVM=ON
else
    ENABLE_LLVM=OFF
fi

mkdir -p build
cd build
cmake .. -G "Unix Makefiles" \
    -DENABLE_LLVM=$ENABLE_LLVM \
    -DENABLE_SAN2NASM=ON \
    -DENABLE_DEBUGGER=ON \
    -DENABLE_OPTIMIZER=ON \
    -DENABLE_SYMBOLIC_TRACE=$ENABLE_SYMBOLIC_TRACE \
    -DENABLE_DLMT_FASTPATH=$ENABLE_DLMT_FASTPATH

cmake --build . --target meralang repl_ui test_capsules

# Post-build: generate .capsule binaries
mkdir -p ../dist
for f in ../examples/*.ml; do
    echo "Compiling $(basename "$f")..."
    ./bin/meralang "$f" -o "../dist/$(basename "$f" .ml).capsule"
done

# Optional: run symbolic trace
if [[ "$ENABLE_SYMBOLIC_TRACE" == "ON" ]]; then
    echo "Running symbolic trace..."
    ./bin/meralang --trace ../examples/trace_test.ml > ../dist/trace_log.txt
fi
