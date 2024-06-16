@ECHO OFF
ECHO Cleaning up build directory...

IF NOT pwd==%cd% (cd /d %~dp0) 
cd ..\..
if exist build RMDIR /S /Q build

ECHO Done.