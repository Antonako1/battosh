#!/bin/bash
set +x
cd $(dirname $0) 
source ./batch/globals.bat 
cd ..  
cd ../build  
cp ../test/test.bat ./win/test.bat 
cp ../extern_dependencies/ATRC/libs/win/* ./win/ 

ATRC_PATH="C:/Users/$USER/battosh/ATRC" 
if [ ! -e $ATRC_PATH ]; then
    mkdir $ATRC_PATH     
fi
cp ../ATRC/* $ATRC_PATH 
echo "" 
echo "" 
./win/$PROJECTNAME.exe $*
echo $? 
cp ./win/*.sh ../test 
cd ..  
