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
    // TODO check if file is .bat or .cmd
    info->INPUT_FILE = std::make_unique<std::string>(argv[1]);
    bool output_provided = false;
    bool shell_provided = false;
    
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help") {
            std::string err_msg = "Help message";
            message(err_msg, FL_FLAG_BATTOSH, HELP_, true, -1, -1);
        } else if (std::string(argv[i]) == "--version") {
            std::string err_msg = "battosh version";
            message(err_msg, FL_FLAG_BATTOSH, VERSION_, true, -1, -1);
        } else if (std::string(argv[i]) == "--wsl") {
            if (info->_linux_battosh) {
                std::string error = "WSL and LINUX flags cannot be used together";
                message(error, FL_FLAG_BATTOSH, HELP_, true, -4, -4);
            }
            info->wsl = true;
        } else if (std::string(argv[i]) == "--linux") {
            if (info->wsl) {
                std::string error = "WSL and LINUX flags cannot be used together";
                message(error, FL_FLAG_BATTOSH, HELP_, true, -4, -4);
            }
            info->_linux_battosh = true;
        } else if (std::string(argv[i]) == "-o" || std::string(argv[i]) == "--out") {
            if (i + 1 < argc) {
                info->OUTPUT_FILE = std::make_unique<std::string>(argv[i + 1]);
                output_provided = true;
                i++;
            } else {
                std::string error = "Output file not provided";
                message(error, FL_FLAG_BATTOSH, HELP_, true, -3, -3);
            }
        } else if (std::string(argv[i]) == "--save-whitespace" || std::string(argv[i]) == "-sw"){
            info->savewhitespace = true;
        } else if (std::string(argv[i]) == "--save-comments" || std::string(argv[i]) == "-sc"){
            info->savecomments = true;
        }else if (std::string(argv[i]) == "--set-shell"){
            if (i + 1 < argc) {
                info->SHELL = std::make_unique<std::string>(argv[i + 1]);
                i++;
                shell_provided = true;
            } else {
                std::string error = "Shell not provided";
                message(error, FL_FLAG_BATTOSH, HELP_, true, -3, -3);
            }
        } else if(std::string(argv[i]) == "-dr" || std::string(argv[i]) == "--dir-sort"){
            info->dirsort = true;
        }

        else if (std::string(argv[i]) == "-bs" || std::string(argv[i]) == "--bat-shell"){
            info->batchtoshell = true;
        }
        
        else if (std::string(argv[i]) == "--set-mkdirp"){
            info->mkdir_p = true;
        } else if (std::string(argv[i]) == "-qm" || std::string(argv[i]) == "--quiet-mode"){
            info->quiet = true;
        } 
        
        else {
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

    if (!shell_provided) {
        info->SHELL = std::make_unique<std::string>("bash");
    }

    
    std::vector<Token> *tokens = lexical(info.get());

    std::vector<ParsedToken> *parsed_tokens = parse(tokens, info.get());

    tosh(parsed_tokens, info.get());

    delete tokens;
    return 0;
}