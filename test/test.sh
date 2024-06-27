#!/bin/bash
Testdirpath="$HOME/testdir123" 
if [ ! -e $Testdirpath ]; then
    mkdir $Testdirpath     
fi
# This is a temporary fix. it turns off case ignoring in if statements
shopt -u nocasematch
read -p "Delete directory '$Testdirpath'?" QUESTION 


shopt -s nocasematch
if [[ "$QUESTION" == "y"  ]]; then    
    rmdidsr $Testdirpath     
    
fi
# This is a temporary fix. it turns off case ignoring in if statements
shopt -u nocasematch

