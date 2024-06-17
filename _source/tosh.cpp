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
    // Save output to file
    std::ofstream file(*args->OUTPUT_FILE);
    if (!file.is_open()) {
        std::cerr << "ERROR OPENING FILE: " << *args->OUTPUT_FILE << std::endl;
        exit(1);
    }
    for(const auto &parsed_token : *tokens){
        switch(parsed_token.command){
            case ECHO: {
                output += "echo ";
                for(const auto &value : parsed_token.values){
                    output += value + " ";
                }
                output += "\n";
                break;
            }
            case ENDLINE: {
                output += "\n";
                break;
            }
        }
    }

    file << output;
    file.close();
}