#!/bin/bash
if [ -e data]; then
    if [ ! -e "ququ"]; then
        echo w 
    else
        echo q 
    fi
elif [ -e "haha"]; then
    echo Hi from the other side 
    if [ ! -e "ququ"]; then
        echo w 
    else
        echo q 
    fi
else
    echo data exists 
    if [ ! -e "ququ"]; then
        echo w 
    else
        echo q 
    fi
fi

$SHELL --version
clear
call haha 
cat test.txt 
# TEST 
echo Hi 
cd "C:\temp" 
exit 10 

cmake --build . --target test 

if [ ! -e data]; then
    echo data does not exist 
else
    echo data exists 
fi

if [ "A" = "A" ]; then
    echo test 
fi
