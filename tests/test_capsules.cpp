#include "../src/capsule_runner.cpp"
#include <cassert>
#include <sstream>
#include <fstream>

void runTest(const std::string& file, const std::string& expected) {
    std::ostringstream captured;
    std::streambuf* old = std::cout.rdbuf(captured.rdbuf());
    CapsuleRunner::executeCapsule(file);
    std::cout.rdbuf(old);
    assert(captured.str().find(expected) != std::string::npos);
    std::cout << "[PASS] " << file << " contains \"" << expected << "\"\n";
}

int main() {
    runTest("sample/blur_filter.mera", "[RUN] Executing Capsule");
    runTest("sample/blur_filter.mera", "[INSPECT] Memory dump simulated.");
    std::cout << "All tests passed.\n";
    return 0;
}
