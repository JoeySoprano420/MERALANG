#include <iostream>
#include <string>
#include "../src/capsule_runner.cpp"

int main() {
    std::string input;
    std::cout << "MeraLang REPL Debugger\nType a .mera capsule file to execute or :quit\n";
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input == ":quit") break;
        CapsuleRunner::executeCapsule(input);
    }
    return 0;
}
