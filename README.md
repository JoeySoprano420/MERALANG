# MERALANG


* Modular Enhanced Reborn Assembled Language (MeraLang) 


* Complements other languages	For performance-critical code


* Modernized with new structure	Updated tooling, macros, and IDE integration


* Modified with custom tweaks	User-defined extensions and opcode mapping


* Radically reimagined	Symbolic assembly with introspection 


* Responds to runtime state	toggleable Event-driven and introspective assembly (rare)



## Here is the **official merged MeraLang v1.0 Syntax + Execution Cheat Sheet**, capturing the fusion between **symbolic introspection** (`DG Tracing`) and **hardware-level performance** (`DLMT Mapping`), optimized for educational clarity *and* real-world execution power.

---

## 🧠 MeraLang Hybrid Syntax: Symbolic Meets Hardware

| **Construct**          | **Symbolic Feature**                | **DLMT Mapping**                    | **Low-Level Equivalent**    |
| ---------------------- | ----------------------------------- | ----------------------------------- | --------------------------- |
| `val`                  | Strong static typed declaration     | Mapped to reg or mem alloc          | `mov` / `push`              |
| `derive x from y by z` | Symbolic arithmetic with trace      | e.g. `ADD_VAR x, z`                 | `add eax, [z]`              |
| `loop i from a to b`   | Introspective iteration tracing     | loop w/ bounds checking             | `mov`, `cmp`, `jl`, `jmp`   |
| `macro name(args)`     | Reusable symbolic block             | Compiled inline or call w/ metadata | inline NASM or call rel32   |
| `try / catch`          | Capsule exception model             | Symbolic checkpoint tagging         | unwind table / jump handler |
| `rewind capsule`       | Deterministic recovery              | JIT patch to prior state snapshot   | mem state restore           |
| `optimize`             | Toggle off tracing for perf         | Enable fast DLMT execution path     | skip introspection ops      |
| `inspect target`       | Debug memory / register / structure | Injects visual tracer               | mem dump or stack trace     |
| `when state ==`        | Symbolic runtime flags              | Injects conditional tracing logic   | `cmp` / `jz`                |
| `memwrite loc, val`    | Direct memory manipulation          | SAN-level mem mapping               | `mov [loc], val`            |
| `say "..."`            | Symbolic printf + trace log         | Call to I/O tracing engine          | `puts`, `syscall`, etc.     |

---

## 🔣 Capsule Anatomy

```mera
capsule <name>:
    [meta + permissions + optimize toggle]
    [code block]
end
```

### Example:

```mera
capsule filter_image:
  optimize
  loop x from 1 to width - 1:
    loop y from 1 to height - 1:
      val blurred = blur_pixel(x, y)
      image_out[x][y] = blurred
  end
end
```

---

## 🧩 Shorthand Assembly Notation (SAN)

| **SAN Op**         | **Expands To**                            |
| ------------------ | ----------------------------------------- |
| `ADD_VAR a, b`     | `mov eax, [a]` → `add eax, [b]`           |
| `DIV_CONST a, c`   | `mov eax, [a]` → `mov ecx, c` → `div ecx` |
| `MOV_MEM dst, src` | `mov [dst], [src]`                        |

---

## 🔁 Loop & Control Flow

```mera
loop i from 0 to 10:
    say "i = {i}"
end

when i > 5:
    say "over halfway"
end
```

---

## 🧠 Rewindable Execution & Debugging

```mera
capsule compute:
  try:
    val result = risky_op()
    say "Result: {result}"
  catch error == "overflow":
    rewind capsule
    say "Recovered from overflow"
  end
end
```

---

## 🔬 Symbolic Debugging

```mera
when state == "debug":
    inspect memory
    inspect image_out
end
```

---

## 🔒 Symbolic Permissions (Example Metadata)

```mera
capsule secure_write:
  permissions:
    read: image
    write: image_out
    mem: sandboxed
  try:
    memwrite image_out[x][y], 255
  catch error == "overflow":
    rewind capsule
  end
end
```

---

## ⚡ DLMT Toggle Performance Optimizations

```mera
capsule numeric_heavy:
  optimize  # disables tracing, enables SIMD
  val sum = 0
  loop i from 0 to 1024:
    derive sum from sum by data[i]
  end
  say "Sum: {sum}"
end
```

* `optimize` triggers:

  * DLMT mappings
  * SIMD/AVX usage
  * JIT hotspot detection

---

## 🧬 GPU Integration (OpenCL)

```mera
capsule gpu_process:
  kernel gpu_blur:
    input: image
    output: image_out
    logic: blur_pixel(x, y)
  run kernel on GPU
end
```

---

## 🖥️ Visual Capsule Debugger

* **Live Opcode Tracing**: Shows NASM/SAN instructions per line.
* **Memory Map**: Realtime view of capsule memory.
* **State Rewind Panel**: Step-through execution and rollback.

---

## 📂 File Format `.mera`

A `.mera` capsule contains:

* Symbolic source
* SAN/NASM assembly
* DG trace logs
* Permission maps
* Optimization toggles
* Replay checkpoints

---

## 📌 Example: Image Filter with Debug Toggle

```mera
macro blur_pixel(x, y):
  val sum = 0
  loop dx from -1 to 1:
    loop dy from -1 to 1:
      val px = image[x + dx][y + dy]
      derive sum from sum by px
  val avg = sum / 9
  return avg
end

capsule filter_image:
  loop x from 1 to width - 1:
    loop y from 1 to height - 1:
      val blurred = blur_pixel(x, y)
      image_out[x][y] = blurred
  when state == "debug":
    inspect image_out
  end
end
```

---

## 🛠️ Developer Toolkit

| Tool               | Purpose                                    |
| ------------------ | ------------------------------------------ |
| `merac`            | MeraLang compiler (source → bin)           |
| `capsule-run`      | Executes `.mera` capsules                  |
| `dg-trace`         | Dumps DG symbol tree and introspection log |
| `san2nasm`         | Converts SAN instructions into raw NASM    |
| `capsule-debugger` | Live step debugger and memory visualizer   |
| `capsule-opt`      | Profile-guided optimizer for hot sections  |

---

**"Merged syntax cheat sheet"**, which outlines the capabilities and philosophy behind **MeraLang v1.0**, a symbolic and performance-oriented programming language:

---

## 🧠 Summary: MeraLang v1.0 Cheat Sheet

**MeraLang** merges symbolic introspection with hardware-level optimization, creating a language ecosystem that is both **safe** and **high-performance**. It introduces a hybrid syntax combining **DG Tracing** (symbolic execution) and **DLMT Mapping** (direct assembly control), supported by a capsule-based execution model.

### 🔧 Core Features
- **DG Tracing**: Base-12 symbolic numeric system for introspective debugging.
- **DLMT Mapping**: Direct translation from high-level syntax to x86/x64 MASM assembly.
- **Capsule Execution Model**: Self-contained units with metadata, sandboxing, and rewind/replay APIs.
- **Visual Capsule Debugger**: Live opcode tracing and memory inspection.
- **Split/Toggled JIT**: Selective optimization of performance hotspots.
- **SAN (Shorthand Assembly Notation)**: Readable low-level syntax for direct control.
- **Cross-Platform Targets**: WASM, FPGA, x86/ARM, OpenCL GPU.

### 🧩 Developer Experience
- Multi-paradigm support: procedural, functional, declarative.
- Plugin hooks for IDE integration and AI modeling.
- Strong static typing and symbolic permission maps.
- Exception handling with symbolic checkpoints and rewind logic.

### 🚀 Strategic Benefits
- Safer systems programming via sandboxing and opcode verification.
- Transparent debugging for critical domains (aerospace, medical, finance).
- Performance without sacrificing readability.
- Educational tooling for teaching compiler theory and systems programming.
- Adaptive runtime for AI and emergent systems.

---

## 🔍 Expansion: Why MeraLang Matters

### 1. **Symbolic Fidelity Meets Hardware Precision**
MeraLang’s fusion of symbolic logic and direct assembly control is rare. Most languages sacrifice one for the other. Here, **DG IR** enables introspective debugging, while **DLMT** ensures raw performance. This duality is ideal for domains requiring both **traceability** and **speed**, such as scientific computing and embedded systems.

### 2. **Capsule Architecture as a Paradigm Shift**
Capsules encapsulate execution logic, metadata, and introspection tools. This modularity allows for:
- **Secure execution** (sandboxing, permission maps)
- **Deterministic debugging** (rewind/replay APIs)
- **Cross-domain deployment** (WASM, FPGA, native binaries)

It’s a step toward **self-contained, introspective software agents**—a concept with implications for AI, simulation, and autonomous systems.

### 3. **Educational and Research Utility**
The visual debugger, symbolic tracing, and macro system make MeraLang a powerful teaching tool. It demystifies low-level programming while preserving high-level expressiveness. This could revolutionize how compiler design and systems programming are taught.

### 4. **Adaptive Execution and AI Integration**
Runtime toggles, symbolic state awareness, and plugin hooks pave the way for **adaptive software**—programs that can introspect, modify themselves, and respond to changing conditions. This is foundational for **emergent systems** and **AI agents** that evolve over time.

---

Here are the **complete and detailed setup instructions** for installing, running, building, testing, and using the **MeraLang v1.0 system** on **Windows**, **Linux**, and **macOS**.

---

# 🌐 MeraLang v1.0 — Full Installation & Usage Guide

---

## 📁 FILE STRUCTURE OVERVIEW

```
MeraLang/
├── build/                      # Build scripts (.bat / .sh)
│   ├── build.bat
│   └── build.sh
├── installer/                 # Windows installer script
│   ├── build_installer.bat
│   └── meralang_installer.iss
├── meralang-vsix/            # VSCode Extension
│   ├── package.json
│   ├── syntaxes/meralang.tmLanguage.json
│   └── scripts/build_publish.sh
├── sample/                   # Sample .mera capsules
│   └── blur_filter.mera
├── trace_logs/               # Execution trace logs
│   └── blur_filter.trace
├── src/                      # Source code of the compiler
│   ├── main.cpp
│   ├── lexer.cpp / lexer.h
│   ├── parser.cpp / parser.h
│   ├── ir_generator.cpp
│   ├── nasm_emitter.cpp
│   ├── llvm_bridge.cpp
│   └── capsule_runner.cpp
├── tools/                    # REPL Debugger UI
│   └── repl_ui.cpp
├── tests/                    # Test suite
│   └── test_capsules.cpp
└── CMakeLists.txt            # Build descriptor
```

---

## 🪟 WINDOWS INSTALLATION

### Prerequisites:

* [Visual Studio 2022](https://visualstudio.microsoft.com/) (with **C++** and **CMake** workloads)
* [NASM](https://www.nasm.us/)
* [LLVM/Clang](https://releases.llvm.org/)
* [Inno Setup](https://jrsoftware.org/isdl.php) for installer
* [Node.js + VSCE](https://code.visualstudio.com/api/get-started/your-first-extension)

---

### 🔧 Step-by-Step:

#### 1. **Clone and Build MeraLang Compiler**

```cmd
cd MeraLang
build\build.bat
```

This will:

* Generate the build directory
* Compile the entire MeraLang compiler via Visual Studio CMake generator
* Produce: `meralang.exe`, `repl_ui.exe`

#### 2. **Run REPL or Capsule**

```cmd
tools\repl_ui.exe
```

Type:

```
sample\blur_filter.mera
```

#### 3. **Run Capsule Directly**

```cmd
meralang.exe sample\blur_filter.mera
```

---

#### 4. **Run Unit Tests**

```cmd
build\tests\Debug\test_capsules.exe
```

---

#### 5. **Build Windows Installer**

```cmd
installer\build_installer.bat
```

Creates `meralang-setup.exe`

---

#### 6. **Build and Install VSCode Extension**

```bash
cd meralang-vsix
bash scripts/build_publish.sh
```

Then run:

```bash
code --install-extension meralang-extension-1.0.0.vsix
```

---

## 🐧 LINUX INSTALLATION

### Prerequisites:

```bash
sudo apt update
sudo apt install build-essential cmake clang llvm nasm nodejs npm
```

---

### 🔧 Step-by-Step:

#### 1. **Clone and Build MeraLang**

```bash
cd MeraLang
bash build/build.sh
```

This generates `meralang` and `repl_ui` binaries.

#### 2. **Run REPL**

```bash
./tools/repl_ui
```

Or run:

```bash
./meralang sample/blur_filter.mera
```

---

#### 3. **Run Tests**

```bash
./tests/test_capsules
```

---

#### 4. **Install VSCode Extension**

```bash
cd meralang-vsix
bash scripts/build_publish.sh
code --install-extension meralang-extension-1.0.0.vsix
```

---

## 🍎 macOS INSTALLATION

### Prerequisites:

* [Xcode Command Line Tools](https://developer.apple.com/xcode/)
* Homebrew (install from [https://brew.sh/](https://brew.sh/))

```bash
brew install cmake llvm nasm node
```

---

### 🔧 Step-by-Step:

#### 1. **Build the Compiler**

```bash
cd MeraLang
bash build/build.sh
```

#### 2. **Run REPL**

```bash
./tools/repl_ui
```

#### 3. **Execute Capsule**

```bash
./meralang sample/blur_filter.mera
```

#### 4. **Run Tests**

```bash
./tests/test_capsules
```

---

#### 5. **VSCode Extension Setup**

```bash
cd meralang-vsix
bash scripts/build_publish.sh
code --install-extension meralang-extension-1.0.0.vsix
```

---

## 🔬 LANGUAGE USAGE EXAMPLES

### 📜 Declaring a Variable

```mera
val x = 10
```

### 🧮 Arithmetic

```mera
derive sum from sum by x
val avg = sum / 9
```

### 🔁 Loops

```mera
loop i from 0 to 10:
  say "Step {i}"
end
```

### 📦 Capsule Structure

```mera
capsule main:
  val x = 5
  say "Hello"
end
```

### 🪛 Debugging

```mera
when state == "debug":
  inspect memory
end
```

---

## ✅ VERIFYING YOUR SETUP

To verify full system health:

```bash
meralang sample/blur_filter.mera > out.asm
cat trace_logs/blur_filter.trace
./tests/test_capsules
```

---

## 📦 WHAT YOU GET

| Feature              | Description               |
| -------------------- | ------------------------- |
| `meralang.exe`       | Compiler CLI              |
| `repl_ui.exe`        | Interactive REPL debugger |
| `.vsix`              | VSCode extension          |
| `meralang-setup.exe` | Installer                 |
| `test_capsules`      | Testing framework         |
| `.mera` files        | Symbolic capsules         |
| `.trace` files       | Execution logs            |


---


Example of VS Code extension / Banner:

<img width="1024" height="1024" alt="ChatGPT Image Aug 4, 2025, 05_15_21 AM" src="https://github.com/user-attachments/assets/ae2b2104-9aae-4fda-b493-2ffdad200368" />
