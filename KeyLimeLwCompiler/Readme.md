# KeyLime LW (MeraLang Lite Weight Compiler)

A minimalist, Windows-ready, cross-platform compiler/interpreter for MeraLang capsules.

## Quickstart (Windows)

1. Build (MSVC/MinGW):

build.bat

2. Interpret sample:

run.bat

3. Compile to NASM:

build\keylime-lw.exe samples\blur_filter.mera –emit-nasm
nasm -f win64 output.asm -o output.obj
link /subsystem:console output.obj
output.exe

---

## Features

- Capsule/macro parsing
- NASM emission
- Interpreter for quick runs
- Pure C++17, zero dependencies

See [MeraLang README](https://github.com/JoeySoprano420/MERALANG/blob/main/README.md) for full language details.

🚀 INSTRUCTIONS – WINDOWS QUICKSTART
	1.	Extract or create the folder structure as above.
	2.	Install CMake and a C++ compiler (MSVC or MinGW).
	3.	Run build.bat to build.
	4.	Run run.bat to test-interpret a capsule.
	5.	Emit NASM with:
build\keylime-lw.exe samples\blur_filter.mera --emit-nasm
	6.	Assemble/Link with NASM/MSVC or MinGW.
