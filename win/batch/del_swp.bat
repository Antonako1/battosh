@echo off
cd /D %~dp0
cd ..\..\_source
DEL /S /Q *.swp
cd ..