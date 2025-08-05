cmake_minimum_required(VERSION 3.14)
project(KeyLimeLW
  VERSION 0.1
  LANGUAGES CXX
  DESCRIPTION "Key Lime LW: Lightweight MeraLang Capsule Compiler"
)

# Recommended modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output dirs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Project sources
file(GLOB_RECURSE SOURCES
  src/*.cpp
  include/*.h
)

# Main executable
add_executable(keylime
  src/main.cpp
  src/lexer.cpp
  src/parser.cpp
  src/san_emitter.cpp
  src/dlmt_mapper.cpp
  src/dg_tracer.cpp
  src/capsule_runner.cpp
)

target_include_directories(keylime PRIVATE include)

# Add tests (optional)
enable_testing()
add_subdirectory(tests)

# Examples (not built, but installed)
install(DIRECTORY examples/ DESTINATION share/keylimelw/examples)

# Install the binary and headers
install(TARGETS keylime DESTINATION bin)
install(DIRECTORY include/ DESTINATION include/keylimelw)

# Packaging options (optional)
set(CPACK_PACKAGE_NAME "KeyLimeLW")
set(CPACK_PACKAGE_VERSION "0.1")
set(CPACK_PACKAGE_DESCRIPTION "Key Lime LW: Lightweight MeraLang Capsule Compiler")
set(CPACK_GENERATOR "ZIP;TGZ")
include(CPack)
