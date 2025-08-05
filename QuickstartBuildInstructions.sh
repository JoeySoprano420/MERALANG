# Clone the project
git clone https://github.com/YourOrg/KeyLimeLW.git
cd KeyLimeLW

# Build (all platforms)
mkdir build && cd build
cmake ..
make      # or 'cmake --build .'

# Run an example (after build)
./bin/keylime ../examples/blur_filter.mera --run
