@echo off
REM Windows build script for KeyLime LW
if not exist build mkdir build
cd build
cmake ..
cmake --build . --config Release
cd ..
echo Build complete. EXE is at build\keylime-lw.exe
pause
