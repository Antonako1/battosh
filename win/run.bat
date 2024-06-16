@echo off
IF NOT pwd==%cd% (cd /d %~dp0) 
call .\batch\globals.bat
cd ..
cd ..\build
.\win\%PROJECTNAME%.exe %*
cd ..