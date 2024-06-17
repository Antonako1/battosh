@echo off
cd /d %~dp0
call .\batch\globals.bat
cd ..
cd ..\build
copy ..\test\test.bat .\win\test.bat
.\win\%PROJECTNAME%.exe %*
echo %ERRORLEVEL%
copy .\win\*.sh ..\test
cd ..