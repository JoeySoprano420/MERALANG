; MeraLang → LLVM IR Mapping

; === Module Header ===
source_filename = "meralang.ll"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [14 x i8] c"Hello, %s\00", align 1

; === Function Definitions ===
define i32 @main() {
entry:
    ; val x = 5
    %x = alloca i32
    store i32 5, i32* %x

    ; derive sum from a by b → sum = a + b
    %a = load i32, i32* @a
    %b = load i32, i32* @b
    %add = add i32 %a, %b
    store i32 %add, i32* @sum

    ; say "Hello"
    %msg = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str, i32 0, i32 0), i8* null)

    ret i32 0
}

declare i32 @printf(i8*, ...)

global @a = global i32 1
global @b = global i32 2
global @sum = global i32 0
