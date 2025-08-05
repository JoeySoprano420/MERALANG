#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <cctype>
#include <stdexcept>

// Simple expression evaluator for MeraLang
class MeraLang {
    std::unordered_map<std::string, int> variables;

    int eval_expr(const std::string& expr) {
        std::istringstream iss(expr);
        int result = 0, value = 0;
        char op = '+';
        while (iss >> std::ws) {
            if (std::isdigit(iss.peek())) {
                iss >> value;
            } else if (std::isalpha(iss.peek())) {
                std::string var;
                iss >> var;
                if (variables.count(var)) {
                    value = variables[var];
                } else {
                    throw std::runtime_error("Undefined variable: " + var);
                }
            } else {
                iss >> op;
                continue;
            }
            switch (op) {
                case '+': result += value; break;
                case '-': result -= value; break;
                case '*': result *= value; break;
                case '/': 
                    if (value == 0) throw std::runtime_error("Division by zero");
                    result /= value; break;
                default: throw std::runtime_error("Invalid operator");
            }
            op = iss.peek();
            if (op == '+' || op == '-' || op == '*' || op == '/') {
                iss >> op;
            } else {
                op = '+';
            }
        }
        return result;
    }

public:
    void run(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Cannot open file: " << filename << std::endl;
            return;
        }
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string token;
            iss >> token;
            if (token == "let") {
                std::string var, eq;
                iss >> var >> eq;
                if (eq != "=") {
                    std::cerr << "Syntax error: expected '='\n";
                    continue;
                }
                std::string expr;
                std::getline(iss, expr);
                try {
                    variables[var] = eval_expr(expr);
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            } else if (token == "print") {
                std::string expr;
                std::getline(iss, expr);
                try {
                    std::cout << eval_expr(expr) << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            } else if (token.empty() || token[0] == '#') {
                continue; // skip empty lines or comments
            } else {
                std::cerr << "Unknown statement: " << token << std::endl;
            }
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: MeraLangCompiler <source.ml>\n";
        return 1;
    }
    MeraLang compiler;
    compiler.run(argv[1]);
    return 0;
}

