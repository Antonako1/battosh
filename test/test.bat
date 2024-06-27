@ECHO OFF
setlocal

cd /d %~dp0
call .\batch\msvs-dev-env.bat
cd ..\..
ECHO Building project...

if not exist build mkdir build
cd build

@REM Release version
if "%1" == "Release" (
    "%CMAKEPATH%\CMake\bin\cmake.exe"  -G "Ninja"  -DCMAKE_C_COMPILER:STRING="%COMPILERPATH%" -DCMAKE_CXX_COMPILER:STRING="%COMPILERPATH%" -DCMAKE_BUILD_TYPE:STRING="Release" -DCMAKE_INSTALL_PREFIX:PATH="./install/x64-release"   -DCMAKE_MAKE_PROGRAM="%NINJAPATH%\ninja.exe" ".."
    cmake --build . --config Release
    if %ERRORLEVEL% NEQ 0 (
        ECHO Build failed, exiting...
        exit /B 1
    ) else (
        echo HI
    )

    if not exist test mkdir test
    cd..
    exit /B 0
)

@REM Debug:
"%CMAKEPATH%\CMake\bin\cmake.exe"  -G "Ninja"  -DCMAKE_C_COMPILER:STRING="%COMPILERPATH%" -DCMAKE_CXX_COMPILER:STRING="%COMPILERPATH%" -DCMAKE_BUILD_TYPE:STRING="Debug" -DCMAKE_INSTALL_PREFIX:PATH="./install/x64-debug"   -DCMAKE_MAKE_PROGRAM="%NINJAPATH%\ninja.exe" ".."
if %ERRORLEVEL% NEQ 0 (
    ECHO Build failed, exiting...
    exit /B 1
)
cmake --build . --config Debug

if %ERRORLEVEL% NEQ 0 (
    ECHO Build failed, exiting...
    exit /B 1
)
CD ..
