#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "battosh.hxx"
#include "./commands/commands.hxx"

// NOTE Paths need to end in /
void pathing(ParsedToken &parsed_token, battosh_info *args){
    std::string output = "";
    for(auto &value : parsed_token.values){
        for(auto &c : value){
            if(c == '\\'){
                output += '/';
                continue;
            }
            output += c;
        }
        value = output;
        std::cout << "value: " << value << std::endl;
        output = "";
    }
}