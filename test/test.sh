#!/bin/bash
if [ "A" = "A" echo ]; then
    echo test     
fi

if [ -e data]; then    
    if [ ! -e "ququ"]; then        
        echo w         
    elif [ "A" = "A" ]; then        
        echo e         
        
    else                        
        echo q         
        
    fi

elif [ -e "haha"]; then    
    echo Hi from the other side     
    
else            
    echo data exists     
    
fi


if [ "A" = "A" echo ]; then
    echo test     
fi
