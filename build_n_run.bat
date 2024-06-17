@echo off 
cd /d %~dp0
cd win
call build.bat
call run.bat %*