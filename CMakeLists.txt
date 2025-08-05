cmake_minimum_required(VERSION 3.15)
project(MeraLang LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Compiler warnings ---
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# --- Optional features ---
option(ENABLE_LLVM "Enable LLVM IR backend" ON)
option(ENABLE_SAN2NASM "Enable SAN to NASM converter" ON)
option(ENABLE_DEBUGGER "Enable capsule debugger" ON)
option(ENABLE_OPTIMIZER "Enable capsule optimizer" ON)
option(ENABLE_SYMBOLIC_TRACE "Enable symbolic tracing" ON)
option(ENABLE_DLMT_FASTPATH "Enable DLMT fastpath" OFF)

# --- Core sources ---
add_executable(meralang
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
    src/ir_generator.cpp
    src/nasm_emitter.cpp
    src/llvm_bridge.cpp
    src/capsule_runner.cpp
)

target_include_directories(meralang PRIVATE ${CMAKE_SOURCE_DIR}/src)

# --- Conditional flags ---
if(ENABLE_SYMBOLIC_TRACE)
    target_compile_definitions(meralang PRIVATE DG_TRACE_ENABLED=1)
endif()

if(ENABLE_DLMT_FASTPATH)
    target_compile_definitions(meralang PRIVATE DLMT_FASTPATH=1)
endif()

# --- LLVM integration ---
if(ENABLE_LLVM)
    find_package(LLVM REQUIRED CONFIG)
    if(LLVM_FOUND)
        message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
        target_include_directories(meralang PRIVATE ${LLVM_INCLUDE_DIRS})
        target_link_directories(meralang PRIVATE ${LLVM_LIBRARY_DIRS})
        target_compile_definitions(meralang PRIVATE ${LLVM_DEFINITIONS})
        llvm_map_components_to_libnames(llvm_libs support core irreader)
        target_link_libraries(meralang PRIVATE ${llvm_libs})
    endif()
endif()

# --- Capsule tools ---
if(ENABLE_SAN2NASM)
    add_executable(san2nasm tools/san2nasm.cpp src/nasm_emitter.cpp)
    target_include_directories(san2nasm PRIVATE ${CMAKE_SOURCE_DIR}/src)
endif()

if(ENABLE_DEBUGGER)
    add_executable(capsule_debugger tools/capsule_debugger.cpp src/capsule_runner.cpp)
    target_include_directories(capsule_debugger PRIVATE ${CMAKE_SOURCE_DIR}/src)
endif()

if(ENABLE_OPTIMIZER)
    add_executable(capsule_opt tools/capsule_opt.cpp src/capsule_runner.cpp)
    target_include_directories(capsule_opt PRIVATE ${CMAKE_SOURCE_DIR}/src)
endif()

# --- REPL UI ---
add_executable(repl_ui tools/repl_ui.cpp src/capsule_runner.cpp)
target_include_directories(repl_ui PRIVATE ${CMAKE_SOURCE_DIR}/src)

# --- Tests ---
enable_testing()
add_executable(test_capsules tests/test_capsules.cpp src/capsule_runner.cpp)
add_test(NAME CapsuleTests COMMAND test_capsules)
target_include_directories(test_capsules PRIVATE ${CMAKE_SOURCE_DIR}/src)

# --- Install targets ---
install(TARGETS meralang repl_ui test_capsules
        RUNTIME DESTINATION bin)

if(ENABLE_SAN2NASM)
    install(TARGETS san2nasm RUNTIME DESTINATION bin)
endif()

if(ENABLE_DEBUGGER)
    install(TARGETS capsule_debugger RUNTIME DESTINATION bin)
endif()

if(ENABLE_OPTIMIZER)
    install(TARGETS capsule_opt RUNTIME DESTINATION bin)
endif()

# --- Output directory ---
set_target_properties(meralang repl_ui test_capsules
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# --- Packaging ---
set(CPACK_PACKAGE_NAME "MeraLang")
set(CPACK_PACKAGE_VERSION "1.0")
set(CPACK_PACKAGE_DESCRIPTION "Symbolic Capsule Compiler")
set(CPACK_GENERATOR "ZIP;TGZ")
include(CPack)
