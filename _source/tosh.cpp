#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include "battosh.hxx"
#include "./commands/commands.hxx"

EXIT_FLAG exit_flag;
ECHO_FLAG echo_flag;
// VER_FLAG ver_flag;
// ASSOC_FLAG assoc_flag;

void tosh(std::vector<ParsedToken> *tokens, battosh_info *args){
    std::string output = "";
    for(auto &parsed_token : *tokens){
        std::cout << "---Command: " << parsed_token.command << " Value: '" << parsed_token.value << "' Line: " << parsed_token.line << " Column: " << parsed_token.column << std::endl;
        for(auto &flag : parsed_token.flags){
            std::cout << "  ---Flag: " << flag << std::endl;
        }
    }
    output += "#!/bin/bash\n";
    for(const auto &parsed_token : *tokens){
        switch(parsed_token.command){
            case ECHO: {
                // output += "echo ";
                bool updated_path = false;
                for(const auto &flag : parsed_token.flags){
                    // check if flag is found
                    if(flag == echo_flag.GET_HELP){
                        updated_path = true;
                        output += echo_flag.LINUX_GET_GELP_UPDATED_PATH + " ";
                        output += echo_flag.LINUX_GET_HELP + " ";
                        continue;
                    }
                    output += flag + " ";
                }
                if(!updated_path){
                    output += "echo ";
                }
                for(const auto &value : parsed_token.values){
                    output += value + " ";
                }
                break;
            }
            case CLS: {
                output += "clear";
                break;
            }
            case VER: {
                output += "$SHELL --version";
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