@echo off
cd /D %~dp0
cd ..\..
DEL /S /Q *.swp
DEL /S /Q *.*~
cd ..