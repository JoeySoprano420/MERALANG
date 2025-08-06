// Most fundamental, platform-agnostic lexer implementation
#include "lexer.h"
#include <string>
#include <vector>

// --- Self-Contained Universal Definitions ---
// These definitions are self-contained to ensure no external dependencies are needed.
// They mirror the expected structure from "lexer.h" in a universal way.

enum class UniversalTokenType {
    Keyword,
    Identifier,
    Number,
    String,
    Symbol,
    EndOfFile,
    Error
};

struct UniversalToken {
    UniversalTokenType type;
    std::string lexeme;
    int line;
};

// --- Pure C++ Lexer Implementation ---
// This function is written in pure, fundamental C++ for maximum portability.
// It has no reliance on external libraries (like <cctype>) or platform-specific behavior.

std::vector<UniversalToken> lex_universal(const std::string& src) {
    std::vector<UniversalToken> tokens;
    int line_number = 1;
    std::size_t i = 0;
    std::size_t src_len = src.length();

    while (i < src_len) {
        char c = src[i];

        // 1. Handle Whitespace (space, tab, carriage return)
        if (c == ' ' || c == '\t' || c == '\r') {
            i = i + 1;
            continue;
        }

        // 2. Handle Newlines
        if (c == '\n') {
            line_number = line_number + 1;
            i = i + 1;
            continue;
        }

        // 3. Handle Identifiers and Keywords
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_') {
            std::size_t start = i;
            while (i < src_len &&
                   ((src[i] >= 'A' && src[i] <= 'Z') ||
                    (src[i] >= 'a' && src[i] <= 'z') ||
                    (src[i] >= '0' && src[i] <= '9') ||
                    src[i] == '_')) {
                i = i + 1;
            }
            std::string lexeme = src.substr(start, i - start);
            UniversalToken t;
            if (lexeme == "macro" || lexeme == "capsule" || lexeme == "val" ||
                lexeme == "loop" || lexeme == "say" || lexeme == "end") {
                t.type = UniversalTokenType::Keyword;
            } else {
                t.type = UniversalTokenType::Identifier;
            }
            t.lexeme = lexeme;
            t.line = line_number;
            tokens.push_back(t);
            continue;
        }

        // 4. Handle Numbers
        if (c >= '0' && c <= '9') {
            std::size_t start = i;
            while (i < src_len && (src[i] >= '0' && src[i] <= '9')) {
                i = i + 1;
            }
            UniversalToken t;
            t.type = UniversalTokenType::Number;
            t.lexeme = src.substr(start, i - start);
            t.line = line_number;
            tokens.push_back(t);
            continue;
        }

        // 5. Handle Strings
        if (c == '"') {
            i = i + 1; // Skip opening quote
            std::size_t start = i;
            while (i < src_len && src[i] != '"') {
                if (src[i] == '\n') {
                    line_number = line_number + 1;
                }
                i = i + 1;
            }
            UniversalToken t;
            t.type = UniversalTokenType::String;
            t.lexeme = src.substr(start, i - start);
            t.line = line_number;
            tokens.push_back(t);
            if (i < src_len && src[i] == '"') {
                i = i + 1; // Skip closing quote
            }
            continue;
        }

        // 6. Handle Symbols
        if (c == '(' || c == ')' || c == '{' || c == '}' || c == ':' ||
            c == ',' || c == '=' || c == '+' || c == '-' || c == '*' || c == '/') {
            UniversalToken t;
            t.type = UniversalTokenType::Symbol;
            t.lexeme.assign(1, c);
            t.line = line_number;
            tokens.push_back(t);
            i = i + 1;
            continue;
        }

        // 7. Handle Unrecognized Characters
        UniversalToken t;
        t.type = UniversalTokenType::Error;
        t.lexeme.assign(1, c);
        t.line = line_number;
        tokens.push_back(t);
        i = i + 1;
    }

    UniversalToken eof_token;
    eof_token.type = UniversalTokenType::EndOfFile;
    eof_token.line = line_number;
    tokens.push_back(eof_token);

    return tokens;
}
