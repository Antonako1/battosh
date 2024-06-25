#!/bin/bash
set +x
setlocal 

cd %~dp0  
source ./batch/msvs-dev-env.bat 
cd ../..  
echo Building project... 

if [ ! -e build]; then
    mkdir build     
fi
cd build  

# Release version 
if [ "$1" == "Release"  ]; then    
    "$CMAKEPATH/CMake/bin/cmake.exe"     -G     "Ninja"     -DCMAKE_C_COMPILER:STRING="$COMPILERPATH"     -DCMAKE_CXX_COMPILER:STRING="$COMPILERPATH"     -DCMAKE_BUILD_TYPE:STRING="Release"     -DCMAKE_INSTALL_PREFIX:PATH="./install/x64-release"     -DCMAKE_MAKE_PROGRAM="$NINJAPATH/ninja.exe"     ".."     
    cmake     --build     .     --config     Release     
    if [ $? -ne 0  ]; then        
        echo Build failed, exiting...         
        exit 1        
        
fi

cd ..
exit 0

fi


# Debug: "$CMAKEPATH/CMake/bin/cmake.exe" -G "Ninja" -DCMAKE_C_COMPILER:STRING="$COMPILERPATH" -DCMAKE_CXX_COMPILER:STRING="$COMPILERPATH" -DCMAKE_BUILD_TYPE:STRING="Debug" -DCMAKE_INSTALL_PREFIX:PATH="./install/x64-debug" -DCMAKE_MAKE_PROGRAM="$NINJAPATH/ninja.exe" ".." 
if [ $? -ne 0  ]; then    
    echo Build failed, exiting...     
    exit 1    
    
fi

cmake --build . --config Debug 

if [ $? -ne 0  ]; then    
    echo Build failed, exiting...     
    exit 1    
    
fi

cd ..  

