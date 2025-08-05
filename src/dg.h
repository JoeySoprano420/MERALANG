#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

// Dodecagram: Base-12 Numerics + Tracing
struct DGState {
    std::vector<int> trace; // stack of base-12 states

    void push(int x) { trace.push_back(x % 12); }
    void rewind()    { if (!trace.empty()) trace.pop_back(); }
    int  top() const { return trace.empty() ? 0 : trace.back(); }

    std::string dump() const {
        std::ostringstream os;
        os << "[DGTrace] ";
        for (int v : trace) os << v << " ";
        return os.str();
    }
};

// Base-12 conversion
inline std::string to_dodec(int x) {
    const char* digits = "0123456789XE";
    std::string out;
    if (x == 0) return "0";
    while (x) { out = digits[x % 12] + out; x /= 12; }
    return out;
}
