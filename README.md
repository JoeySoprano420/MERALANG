````markdown
# MeraLang — Modular Enhanced Reborn Assembled Language

![MeraLang Logo](./assets/meralang-logo.png)

---

## Overview

**MeraLang** is a powerful, symbolic assembly-inspired programming language designed for **low-level system programming**, **bare-metal development**, and **custom assembler/compiler toolchains**.  
It offers a modern syntax with macro capabilities, rich opcode abstraction, and a modular build system — all designed to produce highly optimized machine code, particularly for x86/x86-64 architectures.

---

## Features

- **Symbolic assembly syntax** with clear mnemonic and operand semantics  
- **First-class macros**: parameterized, recursive, conditional  
- **Opcode abstraction** with data-driven encoding tables  
- **Dodecagram base-12 encoding** for internal symbolic representation  
- **Integrated lexer, parser, macro processor, assembler, linker**  
- **Concurrent multi-file build system with dependency graph and incremental caching**  
- **Extensible opcode import system via JSON**  
- **Debugging support with source mapping and breakpoint management**  
- **Language Server Protocol (LSP) support for VSCode integration**  

---

## Installation

### Prerequisites

- [Node.js](https://nodejs.org/) (for language server)  
- [Visual Studio Code](https://code.visualstudio.com/) (recommended editor)  
- NASM or compatible assembler (for native builds)  
- MeraLang runtime & build tools (see release packages)

### Setup

Clone the repository:

```bash
git clone https://github.com/yourname/meralang.git
cd meralang
````

Install dependencies for language server:

```bash
npm install
```

Build MeraLang compiler tools:

```bash
make all
```

---

## Usage

### Writing MeraLang Source

Create `.mera` files using symbolic assembly mnemonics, macros, and directives.

Example `hello.mera`:

```mera
macro greet(name) {
    say "Hello, " + name
}

capsule Main {
    greet("World")
    ret
}
```

### Command Line

Assemble a single file:

```bash
meraasm hello.mera -o hello.exe
```

Build a multi-file project with dependency resolution and concurrency:

```bash
meraasm src/main.mera src/lib.mera -o output.exe
```

Enable verbose and debug output:

```bash
meraasm hello.mera -o hello.exe --verbose --debug
```

---

## Language Specification

### Syntax

* Mnemonics: `mov`, `add`, `sub`, `call`, `ret`, etc.
* Registers: `eax`, `ebx`, `rcx`, ... `rax`, `r15`
* Immediate values: decimal or hex (`42`, `0x2A`)
* Labels: identifiers followed by colon `start:`
* Macros: `macro <name>(params) { ... }` with recursion and conditionals
* Capsules: named code modules `capsule <Name> { ... }`

### Macros

Macros support parameter substitution, conditional expansion, and recursion.

```mera
macro repeat(n, instr) {
    if n > 0 {
        instr
        repeat(n - 1, instr)
    }
}
```

### Encoding

Instructions are compiled using data-driven opcode tables, supporting multiple operand patterns and encoding forms.

---

## Build System

* Dependency graph and topological sorting
* Incremental builds with content hashing and caching
* Concurrent lexing, parsing, macro expansion, assembly, and linking
* Import opcode datasets from JSON for extensibility

---

## Debugger

* Source map from machine code to source lines
* Breakpoints, watchpoints, and register inspection
* Execution stepping, pause, and continue controls
* GUI and CLI debugger interfaces

---

## Language Server and VSCode Integration

* Syntax highlighting for `.mera` files
* IntelliSense and autocomplete
* Diagnostics and error reporting
* Hover info and signature help
* Go-to-definition and references
* Format-on-save and snippets

---

## Contributing

Contributions are welcome!
Please follow the [Code of Conduct](./CODE_OF_CONDUCT.md) and submit pull requests against the `main` branch.

---

## License

MeraLang is released under the [Sovereign Universal Entity Technical License (S.U.E.T.) v1.0](./LICENSE).

---

## Contact

* GitHub: [github.com/yourname/meralang](https://github.com/joeysoprano420/meralang)


---

## Acknowledgments

Inspired by classic assembly languages, modern compiler theory, and the desire for transparent, modular system development.

---

Enjoy coding in MeraLang! 🚀

```
```
