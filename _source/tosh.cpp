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

void add_end_values(const ParsedToken &parsed_token, std::string &output){
    for(const auto &value : parsed_token.values){
        output += value + " ";
    }
}

void tosh(std::vector<ParsedToken> *tokens, battosh_info *args){
    std::cout << "\n=============\nSTART OF TOSH\n";
    std::string output = "";
    for(auto &parsed_token : *tokens){
        std::cout << "---Command: " << parsed_token.command << " Value: '" << parsed_token.value << "' Line: " << parsed_token.line << " Column: " << parsed_token.column << std::endl;
        for(auto &flag : parsed_token.flags){
            std::cout << "    ---Flag: " << flag << std::endl;
        }
        for(auto &value : parsed_token.values){
            std::cout << "    ---Value: " << value << std::endl;
        }
        std::cout << std::endl;
    }
    output += "#!/bin/bash\n";
    for(const ParsedToken &parsed_token : *tokens){
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
                add_end_values(parsed_token, output);
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
            case CALL:{
                output += "call ";
                // TODO PATH CHECK
                add_end_values(parsed_token, output);
                break;
            }
            case TYPE: {
                output += "cat ";
                // TODO PATH CHECK
                add_end_values(parsed_token, output);
                break;
            }
            case CD: {
                output += "cd ";
                // Flag /D is used to change the drive, no equivalent in linux
                // TODO PATH CHECK
                add_end_values(parsed_token, output);
                break;
            }
            case REM: {
                output += "# ";
                add_end_values(parsed_token, output);
                break;
            }
            case EXIT: {
                output += "exit ";
                bool num_provided = false;
                for(const auto &flag : parsed_token.flags){
                    if(flag == exit_flag.EXIT_CURRENT_BATCH){
                        output += parsed_token.values.at(0);
                        num_provided = true;
                    }
                    else if(flag == exit_flag.GET_HELP){
                        output += exit_flag.LINUX_GET_HELP + " ";
                    }
                }
                if(!num_provided){
                    add_end_values(parsed_token, output);
                }
                break;
            }
            case UNKNOWN:{
                output += parsed_token.value + " ";
                add_end_values(parsed_token, output);
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