#!/bin/bash
set +x

if [ ! -e .git ]; then    
    echo .git not found     
    exit     
    
fi


if [ ! -e .gitignore ]; then    
    echo .gitignore not found     
    exit     
    
fi


git add -A 
git commit -m "delgitig COMMIT" 
git clean -xdn 

echo press y to delete all files from .gitignore (y/n) 

read -p " " delgitig 

if [ $delgitig==y  ]; then    
    git     clean     -xdf     
else            
    git     reset     --soft     HEAD~1     
    git     reset     
    echo nothing deleted     
    
fi

