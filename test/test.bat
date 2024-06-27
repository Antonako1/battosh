set "Testdirpath=%HOMEPATH%/testdir123"
if not exist %Testdirpath% mkdir %Testdirpath%
set /P "QUESTION=Delete directory '%Testdirpath%'?"


if /I "%QUESTION%" == "y" (
    RMDIR %Testdirpath%
)