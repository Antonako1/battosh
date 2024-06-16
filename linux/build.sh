#!/bin/sh
echo "Building project..."

cd "$(dirname "$0")"

. ./shell/globals.sh

cd ..

mkdir -p build
cd build

# For release:
# cmake -G "Ninja" -DCMAKE_C_COMPILER:STRING="%COMPILER_C_PATH%" -DCMAKE_CXX_COMPILER:STRING="%COMPIlER_CXX_PATH%" -DCMAKE_BUILD_TYPE:STRING="Release" -DCMAKE_INSTALL_PREFIX:PATH="./install/x64-release" -DCMAKE_MAKE_PROGRAM="$NINJAPATH" ..
# cmake --build . --config Release

# For debug:
cmake -G "Ninja" -DCMAKE_C_COMPILER="$COMPILER_C_PATH" -DCMAKE_CXX_COMPILER="$COMPIlER_CXX_PATH" -DCMAKE_BUILD_TYPE="Debug" -DCMAKE_INSTALL_PREFIX="./install/x64-debug" -DCMAKE_MAKE_PROGRAM="$NINJAPATH" ..
cmake --build . --config Debug

if [ $? -ne 0 ]; then
    echo "Build failed, exiting..."
    exit 1
fi

cd ..