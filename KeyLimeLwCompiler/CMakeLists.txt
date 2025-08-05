cmake_minimum_required(VERSION 3.16)
project(KeyLimeLW LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(keylime-lw
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
    src/emitter.cpp
    src/interpreter.cpp
    src/utils.cpp
)

target_include_directories(keylime-lw PRIVATE src)
