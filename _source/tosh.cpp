#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include "battosh.hxx"
#include "./commands/commands.hxx"

void tosh(std::vector<ParsedToken> *tokens, battosh_info *args){
    std::string output = "";
    for(auto &parsed_token : *tokens){
        std::cout << "---Command: " << parsed_token.command << " Value: '" << parsed_token.value << "' Line: " << parsed_token.line << " Column: " << parsed_token.column << std::endl;
    }
    output += "#!/bin/bash\n";
    for(const auto &parsed_token : *tokens){
        switch(parsed_token.command){
            case ECHO: {
                output += "echo ";
                for(const auto &value : parsed_token.values){
                    output += value + " ";
                }
                break;
            }
            case REM: {
                output += "#";
                for(const auto &value : parsed_token.values){
                    output += value + " ";
                }
                break;
            }
            case ENDLINE: {
                output += "\n";
                break;
            }
        }
    }


    std::ofstream file(*args->OUTPUT_FILE);
    if (!file.is_open()) {
        std::cerr << "ERROR OPENING FILE: " << *args->OUTPUT_FILE << std::endl;
        exit(1);
    }
    file << output;
    file.close();
}