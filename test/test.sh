#!/bin/bash
set +x
cd %~dp0  
cd win  
source build.bat 
source run.bat $*
