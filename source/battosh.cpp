#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "battosh.hxx"
#include "ATRC_VALUES.hxx"



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
    // bool shell_provided = false;
    bool home_provided = false;
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help") {
            std::string err_msg = "Help message";
            message(err_msg, FL_FLAG_BATTOSH, HELP_, true, -1, -1);
        } 
        else if (std::string(argv[i]) == "--version") {
            std::string err_msg = "battosh version";
            message(err_msg, FL_FLAG_BATTOSH, VERSION_, true, -1, -1);
        } 
        else if (std::string(argv[i]) == "--wsl") {
            // TODO message
            std::cout << "--wsl provided, linux paths automatically turned off\n";
            info->no_linux = true;
            info->wsl = true;
        } 
        else if (std::string(argv[i]) == "--no-linux") {
            info->no_linux = true;
        } 
        else if (std::string(argv[i]) == "-o" || std::string(argv[i]) == "--out") {
            if (i + 1 < argc) {
                info->OUTPUT_FILE = std::make_unique<std::string>(argv[i + 1]);
                output_provided = true;
                i++;
            } else {
                // TODO message
                std::string error = "Output file not provided";
                message(error, FL_FLAG_BATTOSH, HELP_, true, -3, -3);
            }
        } 
        else if (std::string(argv[i]) == "--no-whitespace" || std::string(argv[i]) == "-nw"){
            info->no_whitespace = true;
        } 
        else if (std::string(argv[i]) == "--no-comments" || std::string(argv[i]) == "-nc"){
            info->no_comments = true;
        }
        // else if (std::string(argv[i]) == "--set-shell"){
        //     if (i + 1 < argc) {
        //         info->SHELL = std::make_unique<std::string>(argv[i + 1]);
        //         i++;
        //         shell_provided = true;
        //     } else {
        //         std::string error = "Shell not provided";
        //         message(error, FL_FLAG_BATTOSH, HELP_, true, -3, -3);
        //     }
        // } 
        else if(std::string(argv[i]) == "-dr" || std::string(argv[i]) == "--dir-sort"){
            info->dirsort = true;
        }

        else if (std::string(argv[i]) == "-bs" || std::string(argv[i]) == "--bat-shell"){
            info->batchtoshell = true;
        }
        else if (std::string(argv[i]) == "--set-home"){
            if (i + 1 < argc) {
                info->HOME_PATH = std::make_unique<std::string>(argv[i + 1]);
                i++;
                home_provided = true;
            } else {
                std::string error = "Home path not provided";
                message(error, FL_FLAG_BATTOSH, HELP_, true, -3, -3);
            }
        }
        else if(std::string(argv[i]) == "--disable-atrc-warnings"){
            info->disable_atrc_warnings = true;
        }
        
        else if (std::string(argv[i]) == "--set-mkdirp"){
            info->mkdir_p = true;
        } 
        else if (std::string(argv[i]) == "-qm" || std::string(argv[i]) == "--quiet-mode"){
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

    // moved to tosh
    // if (!shell_provided) {
    //     info->SHELL = std::make_unique<std::string>("bash");
    // }
    std::string temp = "";

    if(!home_provided){
        info->HOME_PATH = std::make_unique<std::string>(get_home_dir(""));
    } else {
        std::string home_path = *info->HOME_PATH;
        if(home_path.back() == '/' || home_path.back() == '\\'){
            home_path = home_path.substr(0, home_path.size() - 1);
        }
        info->HOME_PATH = std::make_unique<std::string>(home_path);
    }
    start_output_log(info.get());
    write_to_output_log("========================================");
    write_to_output_log("Work started. Given info:");
    write_to_output_log("Input file: " + *info->INPUT_FILE);
    write_to_output_log("Output file: " + *info->OUTPUT_FILE);
    write_to_output_log("WSL paths: " + std::to_string(info->wsl));
    write_to_output_log("No linux paths: " + std::to_string(info->no_linux));
    write_to_output_log("No whitespace: " + std::to_string(info->no_whitespace));
    write_to_output_log("No comments: " + std::to_string(info->no_comments));
    write_to_output_log("-p to mkdir: " + std::to_string(info->mkdir_p));
    write_to_output_log("Output to null: " + std::to_string(info->quiet));
    write_to_output_log("Sort directories: " + std::to_string(info->dirsort));
    write_to_output_log("Batch to Shell conversion: " + std::to_string(info->batchtoshell));
    write_to_output_log("Path to home: " + *info->HOME_PATH);
    write_to_output_log("Disable ATRC Warnings: " + std::to_string(info->disable_atrc_warnings));
    write_to_output_log("========================================");


    write_to_output_log("Starting tokenization.");
    std::vector<Token> *tokens = lexical(info.get());
    write_to_output_log("Tokenization finished.");
    write_to_output_log("Created tokens:");
    for(const auto& token : *tokens){
        write_to_output_log("----Enum command: " + std::to_string(token.command));
        write_to_output_log("----Parsed value: " + token.value);
        write_to_output_log("----At line: " + std::to_string(token.line));
        write_to_output_log("----At column: " + std::to_string(token.column));
        write_to_output_log("----Collected flags and attributes:");
        for(const auto& flag: token.flags){
            write_to_output_log("--------Flag: " + flag);
        }
        for(const auto& attrib: token.attributes){
            write_to_output_log("--------Attribute: " + attrib);
        }
        write_to_output_log("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
    }
    write_to_output_log("\n=========================================\n");
    write_to_output_log("Starting parsing.");
    std::vector<ParsedToken> *parsed_tokens = parse(tokens, info.get());
    write_to_output_log("Parsing finished.");
    write_to_output_log("Created Parse tokens:");
    for(const auto& token : *parsed_tokens){
        write_to_output_log("----Enum command: " + std::to_string(token.command));
        write_to_output_log("----Parsed value: " + token.value);
        write_to_output_log("----At line: " + std::to_string(token.line));
        write_to_output_log("----At column: " + std::to_string(token.column));
        write_to_output_log("----Collected values, flags and attributes:");
        for(const auto& flag: token.flags){
            write_to_output_log("--------Flag: " + flag);
        }
        for(const auto& attrib: token.attributes){
            write_to_output_log("--------Attribute: " + attrib);
        }
        for(const auto& value: token.values){
            write_to_output_log("--------Value: " + value);
        }
        write_to_output_log("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
    }
    try {
        write_to_output_log("Turning tokens into shell commands");
        tosh(parsed_tokens, info.get());
        write_to_output_log("Tokens turned into shell commands");
        delete tokens;
        delete parsed_tokens;
        save_output_log();
    } catch (...) {
        delete tokens;
        delete parsed_tokens;
        save_output_log();
        throw;
    }

    return 0;
}