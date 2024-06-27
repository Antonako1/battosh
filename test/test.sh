#!/bin/bash
set +x

source ./batch/msvs-dev-env.bat 
cd ../..  
echo Building project... 

if [ ! -e build ]; then
    mkdir build     
fi
# This is a temporary fix. it turns off case ignoring in if statements
shopt -u nocasematch
cd build  

# Release version 
if [ "$1" == "Release"  ]; then    
    "$CMAKEPATH/CMake/bin/cmake.exe"     -G     "Ninja"     -DCMAKE_C_COMPILER:STRING="$COMPILERPATH"     -DCMAKE_CXX_COMPILER:STRING="$COMPILERPATH"     -DCMAKE_BUILD_TYPE:STRING="Release"     -DCMAKE_INSTALL_PREFIX:PATH="./install/x64-release"     -DCMAKE_MAKE_PROGRAM="$NINJAPATH/ninja.exe"     ".."     
    cmake     --build     .     --config     Release     
    if [ $? -ne 0  ]; then        
        echo Build failed, exiting...         
        exit 1        
    else                        
        echo HI         
    fi
    # This is a temporary fix. it turns off case ignoring in if statements
    shopt -u nocasematch
    
    
    if [ ! -e test ]; then
        mkdir test         
    fi
    # This is a temporary fix. it turns off case ignoring in if statements
    shopt -u nocasematch
    cd ..    
    exit 0    
fi
# This is a temporary fix. it turns off case ignoring in if statements
shopt -u nocasematch


# Debug:
 "$CMAKEPATH/CMake/bin/cmake.exe" -G "Ninja" -DCMAKE_C_COMPILER:STRING="$COMPILERPATH" -DCMAKE_CXX_COMPILER:STRING="$COMPILERPATH" -DCMAKE_BUILD_TYPE:STRING="Debug" -DCMAKE_INSTALL_PREFIX:PATH="./install/x64-debug" -DCMAKE_MAKE_PROGRAM="$NINJAPATH/ninja.exe" ".." 
if [ $? -ne 0  ]; then    
    echo Build failed, exiting...     
    exit 1    
fi
# This is a temporary fix. it turns off case ignoring in if statements
shopt -u nocasematch

cmake --build . --config Debug 

if [ $? -ne 0  ]; then    
    echo Build failed, exiting...     
    exit 1    
fi
# This is a temporary fix. it turns off case ignoring in if statements
shopt -u nocasematch

cd ..  

