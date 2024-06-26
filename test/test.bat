@echo off
cd /d %~dp0
call .\batch\globals.bat
cd ..
cd ..\build
copy /Y ..\test\test.bat .\win\test.bat
copy /B /Y ..\extern_dependencies\ATRC\libs\win\* .\win\

set "ATRC_PATH=C:\Users\%USERNAME%\battosh\ATRC"
if not exist %ATRC_PATH% mkdir %ATRC_PATH%
copy /Y ..\ATRC\* %ATRC_PATH%
echo.
echo %1 %2 %3 %test%2 %2
.\win\%PROJECTNAME%.exe %*
echo %ERRORLEVEL%
copy /Y .\win\*.sh ..\test
cd ..