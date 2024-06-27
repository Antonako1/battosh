#!/bin/bash
shopt -s nocasematch
if [[ "a" == "A"  ]]; then
    shopt -u nocasematch
    echo hi     
fi

shopt -s nocasematch
if [[ "a" == "A"  ]]; then
    shopt -u nocasematch    
    echo hello     
fi
shopt -u nocasematch


if [ "a" == "A"  ]; then    
    echo hello     
fi

