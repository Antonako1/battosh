#!/bin/bash
set +x
cd %~dp0  
source ./batch/globals.bat 
cd ..  
cd ../build  
copy ../test/test.bat ./win/test.bat 
copy ../extern_dependencies/ATRC/libs/win/* ./win/ 

set "ATRC_PATH=C:/Users/$USER/battosh/ATRC" 
if [ ! -e $ATRC_PATH]; then
    mkdir $ATRC_PATH     
fi
copy ../ATRC/* $ATRC_PATH 
echo "" 
echo $1 $2 $3 $test2 $2 
./win/$PROJECTNAME.exe $*
echo $? 
copy ./win/*.sh ../test 
cd ..  
