@echo off
setlocal
cd /d %~dp0
call ..\win\batch\globals.bat
cd /d %~dp0

REM STANDALONE BUILDING
RMDIR /S /Q .\output
set BUILD_DIR=.\output\win
mkdir %BUILD_DIR%
call ..\win\batch\del.bat
call .\win\build.bat "Release"
cd /d %~dp0
COPY /Y/B ..\build\win\%PROJECTNAME%.exe %BUILD_DIR%
"C:\Program Files\7-Zip\7z.exe" a -tzip %BUILD_DIR%\%PROJECTNAME%-win-standalone.zip %BUILD_DIR%\%PROJECTNAME%.exe

REM INSTALLER BUILDING
if not exist %BUILD_DIR%\nsis mkdir %BUILD_DIR%\nsis
COPY .\installer.nsi %BUILD_DIR%\nsis
COPY ..\LICENSE %BUILD_DIR%\nsis
COPY ..\README.md %BUILD_DIR%\nsis
COPY .\setup.ps1 %BUILD_DIR%\nsis
COPY .\uninstall.ps1 %BUILD_DIR%\nsis
MOVE %BUILD_DIR%\%PROJECTNAME%.exe %BUILD_DIR%\nsis
cd %BUILD_DIR%\nsis
makensis installer.nsi
cd ..
MOVE .\nsis\*.exe .
DEL %PROJECTNAME%.exe
MOVE * ..
endlocal