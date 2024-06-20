#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include "battosh.hxx"
#include "./commands/commands.hxx"
#include "ATRC_VALUES.hxx"
#include "../extern_dependencies/ATRC/include/ATRC.h"


EXIT_FLAG exit_flag;
ECHO_FLAG echo_flag;
MKDIR_FLAG mkdir_flag;
RMDIR_FLAG rmdir_flag;
RENAME_FLAG rename_flag;
IF_FLAG if_flag;
TIMEOUT_FLAG timeout_flag;
MOVE_FLAG move_flag;
HELP_FLAG help_flag;
PAUSE_FLAG pause_flag;
DIR_FLAG dir_flag;

void send_message(std::string msg, int errnum, bool disable_atrc_warnings){
    if(errnum == ATRC_NOT_FOUND && disable_atrc_warnings){
        return;
    }
    message(msg, FL_FLAG_TOSH, 
    errnum, false, -1,-1);
}
void add_to_output(std::string &output, const std::string &value){
    output += value;
}

void add_end_values(const ParsedToken &parsed_token, std::string &output){
    for(const auto &value : parsed_token.values){
        output += value + " ";
    }
}

bool check_comparison_in_future(std::vector<ParsedToken> *tokens, size_t i){
    size_t j = i + 1;
    if(tokens->at(j).command == EXIST || tokens->at(j).command == EQU || tokens->at(j).command == NEQ || tokens->at(j).command == LSS || tokens->at(j).command == LEQ || tokens->at(j).command == GTR || tokens->at(j).command == GEQ){
        return true;
    }
    
    return false;
}

bool check_operators_in_future(std::vector<ParsedToken> *tokens, size_t i){
    size_t j = i + 1;
    if(tokens->at(j).command == AND || tokens->at(j).command == OR || tokens->at(j).command == NOT || tokens->at(j).command == SHL || tokens->at(j).command == SHR){
        return true;
    }
    return false;
}

void if_statement_workings(
    std::vector<ParsedToken> *tokens, 
    size_t &i, 
    std::string &output, 
    bool &inside_if,
    int &short_hand_if_statement
    ){
    // statement check
    // loop until the next command or ( or endline
    bool break_statemnt = false;
    bool if_initialized = false;
    std::string statement = "";
    size_t index = 0;
    for(index = i; index < tokens->size(); index++){

        ParsedToken next_token = tokens->at(index);
        switch (next_token.command) {
        case IF: break; // skip, otherwise will appear in default
        case NOT:
            output += "! ";
            break;
        case EQU:
            output += "-eq ";
            break;
        case NEQ:
            output += "-ne ";
            break;
        case LSS:
            output += "-lt ";
            break;
        case LEQ:
            output += "-le ";
            break;
        case GTR:
            output += "-gt ";
            break;
        case GEQ:
            output += "-ge ";
            break;
        case AND:
            output += "&& ";
            break;
        case OR:
            output += "|| ";
            break;
        // TODO: WIP
        // case XOR:
        //     output += "^ ";
        //     break;
        // case SHL:
        //     output += "<< ";
        //     break;
        // case SHR:
        //     output += ">> ";
        //     break;
        case EXIST:
            output += "-e ";
            // expect a file
            index++;
            output += tokens->at(index).value;
            break;
        case LPAREN:
            output += " ]; then";
            if (tokens->at(index + 1).command != ENDLINE) {
                output += "\n";
            }
            if_initialized = true;
            inside_if = true;
            break_statemnt = true;
            break;
        case RPAREN:
        case ELSE:
            break;
        default:
            // breaks otherwise
            // Check for comparison and operators in future
            // so that: if exist file.txt echo "hello world" is possible
            output += next_token.value + " ";
            bool comparison = check_comparison_in_future(tokens, index);
            bool operators = check_operators_in_future(tokens, index);
            if(
                // next_token.command == ENDLINE || 
                next_token.command != UNKNOWN &&
                !comparison &&
                !operators
            ){  
                // rough code
                if(next_token.command != UNKNOWN){
                    index--;
                    // Remove the added token from output
                    output = output.substr(0, output.size() - next_token.value.size() - 1);
                }
                output += "]; then\n";
                break_statemnt = true;
                short_hand_if_statement = 1;
            }
            break;
        } // end switch
        if(break_statemnt){
            break;
        }
    }
    i = index;
}



void tosh(std::vector<ParsedToken> *tokens, battosh_info *args){
    std::string output = "";
    std::string cts1, cts2 = ""; // buffer contents for atrc file reading
    
    

    ReadATRC_VALUES(*args->HOME_PATH);
    
    {
        // Prevent crashing
        ParsedToken parsed_token;
        parsed_token.command = ENDLINE;
        tokens->push_back(parsed_token);        
    }
    std::string QUIET_MODE = "";

    if(args->quiet){
        QUIET_MODE = "2> /dev/null";
    }
    output += "#!/bin/" + *args->SHELL + "\n";
    bool inside_if = false;
    bool if_end = false;
    int short_hand_if_statement = 0; // 0 = false, 1 = true, 2 = first pass, 3 = second pass, 4 = end if statement
    int if_statement_intend = 0;
    bool daw = args->disable_atrc_warnings;
    for(size_t i = 0; i < tokens->size(); i++){
        ParsedToken parsed_token = tokens->at(i);
        std::cout << "Token: " << parsed_token.value << " Command: " << parsed_token.command << std::endl;
        for(const auto &flag : parsed_token.flags){
            std::cout << "  Flag: " << flag << std::endl;
        }
        for (const auto &value : parsed_token.values) {
            std::cout << "  Value: " << value << std::endl;
        }
        for (const auto &attribute : parsed_token.attributes) {
            std::cout << "  Attribute: " << attribute << std::endl;
        }
        if(inside_if || short_hand_if_statement != 0){
            output += std::string(if_statement_intend, ' ');
        }

        switch(parsed_token.command){
            case ECHO: {
                ReadKey(fd_echo.get(), "ECHO", "command", cts1);
                
                bool updated_path = false;
                for(const auto &flag : parsed_token.flags){
                    // check if flag is found
                    if(flag == echo_flag.GET_HELP){
                        updated_path = true;
                        ReadKey(fd_echo.get(), "ECHO", "get_help", cts2);
                        if(cts2 == "") {
                            send_message("[ECHO] GET_HELP not found", ATRC_NOT_FOUND, daw);
                            output += echo_flag.LINUX_GET_GELP_UPDATED_PATH + " ";
                            output += echo_flag.LINUX_GET_HELP + " ";
                        } else {
                            output += cts2;
                        }
                        continue;
                    }
                    output += flag + " ";
                }
                if(!updated_path){
                    if(cts1 == "") {
                        send_message("[ECHO] command not found", ATRC_NOT_FOUND, daw);
                        output += "echo ";
                    } else {
                        output += cts1;
                    }
                }
                add_end_values(parsed_token, output);
                break;
            }
            case CLS: {
                output += "clear";
                break;
            }
            case VER: {
                output += "uname -r";
                break;
            }
            case CALL:{
                // NOTE More checks might be needed
                output += "source ";
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
            case CDBACK:
                output += "cd ..";
                break;
            case CHDIR:
            case CD:
                output += "cd ";
                // Flag /D is used to change the drive, no equivalent in linux
                // TODO PATH CHECK
                add_end_values(parsed_token, output);
                break;
            case ECHOOFF: {
                std::string temp = parsed_token.values[0];
                std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
                if(temp == "off"){
                    ReadKey(fd_echo.get(), "@ECHO", "off", cts1);
                    if(cts1 == "") {
                        send_message("[ECHO] off not found", ATRC_NOT_FOUND, daw);
                        output += "set +x";
                    } else {
                        output += cts1;
                    }
                } else {
                    ReadKey(fd_echo.get(), "@ECHO", "on", cts1);
                    if(cts1 == "") {
                        send_message("[ECHO] on not found", ATRC_NOT_FOUND, daw);
                        output += "set -x";
                    } else {
                        output += cts1;
                    }
                }
                break;
            }
            case HELP:{
                output += "help ";
                for(const auto &flag : parsed_token.flags){
                    if(flag == help_flag.HELP){
                        output += help_flag.LINUX_GET_HELP + " ";
                    }
                }
                break;
            }
            case PAUSE : {
                output += pause_flag.LINUX_PAUSE;
                break;
            }
            case MOVE: {
                output += "mv ";
                // TODO PATH CHECK
                for(const auto &flag : parsed_token.flags){
                    if(flag == move_flag.GET_HELP){
                        output += move_flag.LINUX_GET_HELP + " ";
                    }
                    else if(flag == move_flag.FORCE_MOVE){
                        output += move_flag.LINUX_FORCE_MOVE + " ";
                    }
                    else if(flag == move_flag.PROMPT){
                        output += move_flag.LINUX_PROMPT + " ";
                    }
                }
                add_end_values(parsed_token, output);
                break;
            }
            case REM: {
                ReadKey(fd_comment.get(), "COMMENT", "command", cts1);
                if(cts1 == "") {
                    send_message("[COMMENT] command not found", ATRC_NOT_FOUND, daw);
                    output += "# ";
                } else {
                    output += cts1;
                }
                add_end_values(parsed_token, output);
                break;
            }
            case IF: {
                if_statement_intend += 4;
                output += "if [ ";
                if_statement_workings(tokens, i, output, inside_if, short_hand_if_statement);
                break;
            }
            case REN:
            case RENAME: {
                output += "mv ";
                // TODO PATH CHECK
                for(const auto &flag : parsed_token.flags){
                    if(flag == rename_flag.GET_HELP){
                        output += rename_flag.LINUX_GET_HELP + " ";
                    }
                }
                add_end_values(parsed_token, output);
                break;
            }
            case TIMEOUT:{
                output += "sleep ";
                for(const auto &flag : parsed_token.flags){
                    if(flag == timeout_flag.GET_HELP){
                        output += timeout_flag.LINUX_GET_HELP + " ";
                    } else if (flag == timeout_flag.NO_INTERRUPT){
                        // TODO: Note to user: Linux does not have a no interrupt flag
                        
                    } 
                    // else if (flag == timeout_flag.TIMEOUT){
                    //     output += timeout_flag.LINUX_TIMEOUT + " ";
                    // }
                }
                add_end_values(parsed_token, output);
                break;
            }
            case RPAREN: {
                if(tokens->size() > i + 1 && tokens->at(i + 1).command == ELSE){
                    if(tokens->size() > i + 2 && tokens->at(i + 2).command == IF){
                        if(if_statement_intend > 4){
                            output = output.substr(0, output.size() - 4);
                        }
                        output += "elif [ ";
                        if_statement_workings(tokens, i, output, inside_if, short_hand_if_statement);
                    } else {
                        // output += output[output.size() - 1] == '\n' ? "" : "\n";
                        output = output.substr(0, output.size() - if_statement_intend);
                        if_statement_intend = if_statement_intend-4<0?0:if_statement_intend-4;
                        output += std::string(if_statement_intend, ' ');
                        if_statement_intend += 4;
                        output += "else";
                    }
                } else {
                    // output += output[output.size() - 1] == '\n' ? "" : "\n";
                    if_statement_intend = if_statement_intend - 4 < 0 ? 0 : if_statement_intend - 4;
                    output = output.substr(0, output.size() - if_statement_intend);

                    if(if_statement_intend != 0){
                        output += std::string(if_statement_intend, ' ');
                    }
                    output += "fi\n";
                    inside_if = false;
                }
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
            case RD:
            case RMDIR: {
                bool updated_command = false;
                bool add_quiet_mode = false;
                for(const auto &flag : parsed_token.flags){
                    if(flag == rmdir_flag.GET_HELP){
                        output += "rmdir ";
                        output += rmdir_flag.LINUX_GET_HELP + " ";
                        updated_command = true;
                        continue;
                    } else if(flag == rmdir_flag.REMOVE_DIR_TREE){
                        if(!updated_command) {
                            output += rmdir_flag.LINUX_UPDATED_COMMAND + " ";
                            output += rmdir_flag.LINUX_REMOVE_DIR_TREE + " ";
                            updated_command = true;
                        }
                        continue;
                    } else if(flag == rmdir_flag.QUIET_MODE){
                        add_quiet_mode = true;
                        continue;
                    }
                }
                if(!updated_command){
                    output += "rmdir ";
                }
                add_end_values(parsed_token, output);
                if(add_quiet_mode){
                    output += QUIET_MODE;
                }
                break;
            }
            case MD:
            case MKDIR: {
                output += "mkdir ";
                if(args->mkdir_p){
                    output += "-p ";
                }
                for(const auto &flag : parsed_token.flags){
                    if(flag == mkdir_flag.GET_HELP){
                        output += mkdir_flag.LINUX_GET_HELP + " ";
                    }
                }
                // TODO PATH CHECK
                add_end_values(parsed_token, output);
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

            // TODO WIP
            case DIR: {
                output += "ls ";

                for(const auto &flag : parsed_token.flags){
                    if(flag == dir_flag.GET_HELP){
                        output += dir_flag.LINUX_GET_HELP + " ";
                    }

                }
                // TODO PATH CHECK
                add_end_values(parsed_token, output);
                break;
            }
        }

        if(short_hand_if_statement != 0){
            short_hand_if_statement++;
            if(short_hand_if_statement == 4 || short_hand_if_statement == 3 && tokens->size() == i + 1){
                output += output[output.size() - 1] == '\n' ? "" : "\n";
                output += "fi\n";
                short_hand_if_statement = 0;
                if_statement_intend = if_statement_intend - 4 < 0 ? 0 : if_statement_intend - 4;
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