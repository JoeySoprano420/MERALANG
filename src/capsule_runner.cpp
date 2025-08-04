#include <iostream>
#include <fstream>
#include <string>

namespace CapsuleRunner {
    void executeCapsule(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Failed to open capsule: " << path << "\n";
            return;
        }

        std::string line;
        std::cout << "[RUN] Executing Capsule: " << path << "\n";
        while (std::getline(file, line)) {
            if (line.find("say") != std::string::npos) {
                auto quote = line.substr(line.find('"') + 1);
                quote = quote.substr(0, quote.find('"'));
                std::cout << quote << "\n";
            }
            if (line.find("inspect") != std::string::npos) {
                std::cout << "[INSPECT] Memory dump simulated.\n";
            }
        }
        std::cout << "[END] Capsule complete.\n";
    }
}
