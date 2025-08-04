@echo off
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release

# build/build.sh
#!/bin/bash
mkdir -p build
cd build
cmake ..
make
