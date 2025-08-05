@echo off
setlocal

:: Detect architecture
set ARCH=%PROCESSOR_ARCHITECTURE%
if "%ARCH%"=="AMD64" (
    set ENABLE_DLMT_FASTPATH=ON
    set ENABLE_SYMBOLIC_TRACE=ON
) else (
    set ENABLE_DLMT_FASTPATH=OFF
    set ENABLE_SYMBOLIC_TRACE=OFF
)

:: LLVM detection (basic)
where llvm-config >nul 2>nul
if %ERRORLEVEL%==0 (
    set ENABLE_LLVM=ON
) else (
    set ENABLE_LLVM=OFF
)

:: Configure build
mkdir build
cd build
cmake .. -G "Ninja" ^
    -DENABLE_LLVM=%ENABLE_LLVM% ^
    -DENABLE_SAN2NASM=ON ^
    -DENABLE_DEBUGGER=ON ^
    -DENABLE_OPTIMIZER=ON ^
    -DENABLE_SYMBOLIC_TRACE=%ENABLE_SYMBOLIC_TRACE% ^
    -DENABLE_DLMT_FASTPATH=%ENABLE_DLMT_FASTPATH%

:: Build
cmake --build . --target meralang repl_ui test_capsules

endlocal
