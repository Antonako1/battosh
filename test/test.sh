#!/bin/bash
set +x
cd $(dirname $0) 
source ./batch/globals.bat 
cd ..  
cd ../build  
copy ../test/test.bat ./win/test.bat 
copy ../extern_dependencies/ATRC/libs/win/* ./win/ 

ATRC_PATH="C:/Users/$USER/battosh/ATRC" 
if [ ! -e $ATRC_PATH ]; then
    mkdir $ATRC_PATH     
fi
copy ../ATRC/* $ATRC_PATH 
echo "" 
echo "" 
./win/$PROJECTNAME.exe $*
echo $? 
copy ./win/*.sh ../test 
cd ..  
