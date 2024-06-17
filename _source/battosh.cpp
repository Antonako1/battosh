#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "battosh.hxx"



int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::string err_msg = "Invalid args";
        message(err_msg, FL_FLAG_BATTOSH, HELP_, true, -1, -1);
        return 1;
    }

    auto info = std::make_unique<battosh_info>();
    info->INPUT_FILE = std::make_unique<std::string>(argv[1]);
    bool output_provided = false;
    
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help") {
            std::string err_msg = "Help message";
            message(err_msg, FL_FLAG_BATTOSH, HELP_, true, -1, -1);
        } else if (std::string(argv[i]) == "--version") {
            std::string err_msg = "battosh version 0.0.1";
            std::cout << err_msg << std::endl;
        } else if (std::string(argv[i]) == "--wsl") {
            if (info->linux) {
                std::string error = "WSL and LINUX flags cannot be used together";
                message(error, FL_FLAG_BATTOSH, HELP_, true, -4, -4);
            }
            info->wsl = true;
        } else if (std::string(argv[i]) == "--linux") {
            if (info->wsl) {
                std::string error = "WSL and LINUX flags cannot be used together";
                message(error, FL_FLAG_BATTOSH, HELP_, true, -4, -4);
            }
            info->linux = true;
        } else if (std::string(argv[i]) == "-o" || std::string(argv[i]) == "--out") {
            if (i + 1 < argc) {
                info->OUTPUT_FILE = std::make_unique<std::string>(argv[i + 1]);
                output_provided = true;
                i++;
            } else {
                std::string error = "Output file not provided";
                message(error, FL_FLAG_BATTOSH, HELP_, true, -3, -3);
            }
        } else {
            if (i == 1) {
                continue;
            }
            std::string error = "Invalid args " + std::string(argv[i]) + " provided";
            message(error, FL_FLAG_BATTOSH, HELP_, true, -2, -2);
        }
    }

    if (!output_provided) {
        std::string input_file = *info->INPUT_FILE;
        std::string output_file = input_file.substr(0, input_file.find_last_of(".")) + ".sh";
        info->OUTPUT_FILE = std::make_unique<std::string>(output_file);
    }

    std::cout << "Input file: " << *info->INPUT_FILE << std::endl;
    std::cout << "Output file: " << *info->OUTPUT_FILE << std::endl;
    std::cout << "WSL: " << info->wsl << std::endl;
    std::cout << "LINUX: " << info->linux << std::endl;

    std::vector<Token> *tokens = lexical(info.get());

    for (const auto &token : *tokens) {
        std::cout << "Command: " << token.command << " Value: " << *token.value << " Line: " << token.line << " Column: " << token.column << std::endl;
    }

    delete tokens;
    return 0;
}