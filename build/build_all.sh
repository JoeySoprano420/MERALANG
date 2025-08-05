#!/bin/bash
set -e

# --- Platform detection ---
ARCH=$(uname -m)
if [[ "$ARCH" == "x86_64" ]]; then
    ENABLE_DLMT_FASTPATH=ON
    ENABLE_SYMBOLIC_TRACE=ON
else
    ENABLE_DLMT_FASTPATH=OFF
    ENABLE_SYMBOLIC_TRACE=OFF
fi

# --- LLVM detection ---
if command -v llvm-config &> /dev/null; then
    ENABLE_LLVM=ON
else
    ENABLE_LLVM=OFF
fi

# --- Git commit hash ---
GIT_COMMIT=$(git rev-parse HEAD)

# --- Configure build ---
mkdir -p build
cd build
cmake .. -G "Unix Makefiles" \
    -DENABLE_LLVM=$ENABLE_LLVM \
    -DENABLE_SAN2NASM=ON \
    -DENABLE_DEBUGGER=ON \
    -DENABLE_OPTIMIZER=ON \
    -DENABLE_SYMBOLIC_TRACE=$ENABLE_SYMBOLIC_TRACE \
    -DENABLE_DLMT_FASTPATH=$ENABLE_DLMT_FASTPATH \
    -DBUILD_COMMIT_HASH="$GIT_COMMIT"

cmake --build . --target meralang repl_ui test_capsules

# --- Post-build: capsule generation ---
mkdir -p ../dist
for f in ../examples/*.ml; do
    echo "Compiling $(basename "$f")..."
    ./bin/meralang "$f" -o "../dist/$(basename "$f" .ml).capsule"
done

# --- Symbolic trace logging ---
if [[ "$ENABLE_SYMBOLIC_TRACE" == "ON" ]]; then
    echo "Running symbolic trace..."
    ./bin/meralang --trace ../examples/trace_test.ml > ../dist/trace_log.txt
fi

# --- Capsule metrics ---
echo "Generating capsule metrics..."
./bin/capsule_metrics ../dist/*.capsule > ../dist/metrics_summary.json

# --- Benchmarking ---
echo "Running capsule benchmarks..."
./bin/benchmark_capsules ../dist/*.capsule > ../dist/benchmark_report.txt

# --- Snapshot testing (optional) ---
if [[ -f ../snapshots/golden_trace.txt ]]; then
    echo "Comparing trace snapshot..."
    diff ../snapshots/golden_trace.txt ../dist/trace_log.txt > ../dist/snapshot_diff.txt || echo "Snapshot mismatch detected."
fi

echo "✅ Build complete. Artifacts in dist/"
