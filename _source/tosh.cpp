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

std::string add_end_values_as_string(const ParsedToken &parsed_token){
    std::string output = "";
    for(const auto &value : parsed_token.values){
        output += value + " ";
    }
    return output;
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
    int &short_hand_if_statement,
    bool daw
    ){
    // statement check
    // loop until the next command or ( or endline
    bool break_statemnt = false;
    bool if_initialized = false;
    std::string statement = "";
    size_t index = 0;
    std::string cts1= "";
    for(index = i; index < tokens->size(); index++){

        ParsedToken next_token = tokens->at(index);
        switch (next_token.command) {
        case IF: break; // skip, otherwise will appear in default
        case NOT:
            output += "! ";
            break;
        case EQU:
            ReadKey(fd_relational_operators.get(), "RELATIONAL_OPERATORS", "EQU", cts1);
            if(cts1 == "") {
                send_message("[RELATIONAL_OPERATORS] EQU not found", ATRC_NOT_FOUND, daw);
                output += "-eq ";
            } else {
                output += cts1;
            }
            break;
        case NEQ:
            ReadKey(fd_relational_operators.get(), "RELATIONAL_OPERATORS", "NEQ", cts1);
            if(cts1 == "") {
                send_message("[RELATIONAL_OPERATORS] NEQ not found", ATRC_NOT_FOUND, daw);
                output += "-ne ";
            } else {
                output += cts1;
            }
            break;
        case LSS:
            ReadKey(fd_relational_operators.get(), "RELATIONAL_OPERATORS", "LSS", cts1);
            if(cts1 == "") {
                send_message("[RELATIONAL_OPERATORS] LSS not found", ATRC_NOT_FOUND, daw);
                output += "-lt ";
            } else {
                output += cts1;
            }
            break;
        case LEQ:
            ReadKey(fd_relational_operators.get(), "RELATIONAL_OPERATORS", "LEQ", cts1);
            if(cts1 == "") {
                send_message("[RELATIONAL_OPERATORS] LEQ not found", ATRC_NOT_FOUND, daw);
                output += "-le ";
            } else {
                output += cts1;
            }
            break;
        case GTR:
            ReadKey(fd_relational_operators.get(), "RELATIONAL_OPERATORS", "GTR", cts1);
            if(cts1 == "") {
                send_message("[RELATIONAL_OPERATORS] GTR not found", ATRC_NOT_FOUND, daw);
                output += "-gt ";
            } else {
                output += cts1;
            }
            break;
        case GEQ:
            ReadKey(fd_relational_operators.get(), "RELATIONAL_OPERATORS", "GEQ", cts1);
            if(cts1 == "") {
                send_message("[RELATIONAL_OPERATORS] GEQ not found", ATRC_NOT_FOUND, daw);
                output += "-ge ";
            } else {
                output += cts1;
            }
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
    
    ReadATRC_VALUES(args);

    

    
    {
        // Prevent crashing
        ParsedToken parsed_token;
        parsed_token.command = ENDLINE;
        tokens->push_back(parsed_token);        
    }
    std::string QUIET_MODE = "";
    std::string buffer = "";
    std::string insert1 = "";
    std::string insert2 = "";
    
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
        // std::cout << "Token: " << parsed_token.value << " Command: " << parsed_token.command << std::endl;
        // for(const auto &flag : parsed_token.flags){
        //     std::cout << "  Flag: " << flag << std::endl;
        // }
        // for (const auto &value : parsed_token.values) {
        //     std::cout << "  Value: " << value << std::endl;
        // }
        // for (const auto &attribute : parsed_token.attributes) {
        //     std::cout << "  Attribute: " << attribute << std::endl;
        // }
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
                ReadKey(fd_cls.get(), "CLS", "command", cts1);
                if(cts1 == "") {
                    send_message("[CLS] command not found", ATRC_NOT_FOUND, daw);
                    output += "clear";
                } else {
                    output += cts1;
                }
                break;
            }
            case VER: {
                ReadKey(fd_ver.get(), "VER", "command", cts1);
                if(cts1 == ""){
                    send_message("[VER] command not found", ATRC_NOT_FOUND, daw);
                    output += "uname -r";
                } else {
                    output += cts1;
                }
                break;
            }
            case CALL:{
                // NOTE More checks might be needed
                ReadKey(fd_call.get(), "CALL", "command", cts1);
                // TODO PATH CHECK
                if(cts1 == ""){
                    send_message("[CALL] command not found", ATRC_NOT_FOUND, daw);
                    output += "source ";
                } else {
                    output += cts1;
                }
                add_end_values(parsed_token, output);
                break;
            }
            case TYPE: {
                ReadKey(fd_type.get(), "TYPE", "command", cts1);
                if(cts1 == ""){
                    send_message("[TYPE] command not found", ATRC_NOT_FOUND, daw);
                    output += "cat ";
                } else {
                    output += cts1;
                }
                // TODO PATH CHECK
                add_end_values(parsed_token, output);
                break;
            }
            case CDBACK:
                ReadKey(fd_cd.get(), "CD", "back", cts1);
                if(cts1 == ""){
                    send_message("[CD] back not found", ATRC_NOT_FOUND, daw);
                    output += "cd ..";
                } else {
                    output += cts1;
                }
                break;
            case CHDIR:
            case CD: {
                // TODO PATH CHECK
                buffer = "";
                ReadKey(fd_cd.get(), "CD", "command", cts1);
                if(cts1 == ""){
                    send_message("[CD] command not found", ATRC_NOT_FOUND, daw);
                    buffer += "cd %*% ";
                } else {
                    buffer += cts1;
                }
                insert1 = add_end_values_as_string(parsed_token);
                const std::string *temp[] = {&insert1};
                InsertVar(buffer, temp);
                output += buffer;
                break;
            }
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
                if_statement_workings(tokens, i, output, inside_if, short_hand_if_statement, daw);
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
                        if_statement_workings(tokens, i, output, inside_if, short_hand_if_statement,daw);
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
                ReadKey(fd_exit.get(), "EXIT", "command", cts1);
                if(cts1 == ""){
                    send_message("[EXIT] command not found", ATRC_NOT_FOUND, daw);
                    output += "exit ";
                } else {
                    output += cts1;
                }
                bool num_provided = false;
                for(const auto &flag : parsed_token.flags){
                    if(flag == exit_flag.EXIT_CURRENT_BATCH){
                        ReadKey(fd_exit.get(), "EXIT", "erarcode", cts1);
                        if(cts1 == ""){
                            send_message("[EXIT] errcode not found", ATRC_NOT_FOUND, daw);
                            output += parsed_token.values.at(0);
                        } else {
                            output += cts1;
                            output += parsed_token.values.at(0);
                        }
                        num_provided = true;
                    }
                    else if(flag == exit_flag.GET_HELP){
                        ReadKey(fd_exit.get(), "EXIT", "get_help", cts1);
                        if(cts1 == ""){
                            send_message("[EXIT] get_help not found", ATRC_NOT_FOUND, daw);
                            output += exit_flag.LINUX_GET_HELP + " ";
                        } else {
                            output += cts1;
                        }
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
                bool add_force_mode = false;
                for(const auto &flag : parsed_token.flags){
                    if(flag == rmdir_flag.GET_HELP){
                        ReadKey(fd_rmdir.get(), "RMDIR", "command", cts1);
                        if(cts1 == ""){
                            send_message("[RMDIR] command not found", ATRC_NOT_FOUND, daw);
                            output += "rmdir ";
                        } else {
                            output += cts1;
                        }        
                        ReadKey(fd_rmdir.get(), "RMDIR", "get_help", cts1);
                        if(cts1 == ""){
                            send_message("[RMDIR] get_help not found", ATRC_NOT_FOUND, daw);
                            output += rmdir_flag.LINUX_GET_HELP + " ";
                        } else {
                            output += cts1;
                        }
                        updated_command = true;
                        continue;
                    } else if(flag == rmdir_flag.REMOVE_DIR_TREE){
                        if(!updated_command) {
                            ReadKey(fd_rmdir.get(), "RMDIR", "modified_command", cts1);
                            if(cts1 == ""){
                                send_message("[RMDIR] modified_command not found", ATRC_NOT_FOUND, daw);
                                output += rmdir_flag.LINUX_UPDATED_COMMAND + " ";
                            } else {
                                output += cts1;
                            }
                            updated_command = true;
                            add_force_mode = true;
                        }
                        continue;
                    } else if(flag == rmdir_flag.QUIET_MODE){
                        add_quiet_mode = true;
                        continue;
                    }
                }
                if(!updated_command){
                    if(cts1 == ""){
                        send_message("[RMDIR] command not found", ATRC_NOT_FOUND, daw);
                        output += "rmdir ";
                    } else {
                        output += cts1;
                    }   
                } else if(add_quiet_mode && add_force_mode){
                    ReadKey(fd_rmdir.get(), "RMDIR", "remove_dir_tree_force", cts1);
                    if(cts1 == ""){
                        send_message("[RMDIR] remove_dir_tree_force not found", ATRC_NOT_FOUND, daw);
                        output += rmdir_flag.LINUX_REMOVE_DIR_TREE_FORCE + " ";
                    } else {
                        output += cts1;
                    }
                } else if (!add_quiet_mode && add_force_mode){
                    ReadKey(fd_rmdir.get(), "RMDIR", "remove_dir_tree", cts1);
                    if(cts1 == ""){
                        send_message("[RMDIR] remove_dir_tree not found", ATRC_NOT_FOUND, daw);
                        output += rmdir_flag.LINUX_REMOVE_DIR_TREE + " ";
                    } else {
                        output += cts1;
                    }
                }
                add_end_values(parsed_token, output);
                if(add_quiet_mode){
                    output += QUIET_MODE;
                }
                break;
            }
            case MD:
            case MKDIR: {
                ReadKey(fd_mkdir.get(), "MKDIR", "command", cts1);
                if(cts1 == ""){
                    send_message("[MKDIR] command not found", ATRC_NOT_FOUND, daw);
                    output += "mkdir ";
                } else {
                    output += cts1;
                }
                if(args->mkdir_p){
                    ReadKey(fd_mkdir.get(), "MKDIR", "mkdir_p", cts1);
                    if(cts1 == ""){
                        send_message("[MKDIR] mkdir_p not found", ATRC_NOT_FOUND, daw);
                        output += "-p ";
                    } else {
                        output += cts1;
                    }
                }
                for(const auto &flag : parsed_token.flags){
                    if(flag == mkdir_flag.GET_HELP){
                        ReadKey(fd_mkdir.get(), "MKDIR", "get_help", cts1);
                        if(cts1 == ""){
                            send_message("[MKDIR] get_help not found", ATRC_NOT_FOUND, daw);
                            output += mkdir_flag.LINUX_GET_HELP + " ";
                        } else {
                            output += cts1;
                        }
                    }
                }
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
    // create message()
    std::cout << "File created: " << *args->OUTPUT_FILE << std::endl;
    std::cout << "Ran with flags:" << std::endl;
    std::cout << "wsl paths: " << args->wsl << std::endl;
    std::cout << "linux paths: " << args->_linux_battosh << std::endl;
    std::cout << "save whitespace: " << args->savewhitespace << std::endl;
    std::cout << "save comments: " << args->savecomments << std::endl;
    std::cout << "shell: " << *args->SHELL << std::endl;
    std::cout << "mkdir_p: " << args->mkdir_p << std::endl;
    std::cout << "quiet: " << args->quiet << std::endl;
    std::cout << "dirsort: " << args->dirsort << std::endl;
    std::cout << "batchtoshell: " << args->batchtoshell << std::endl;
    std::cout << "home path: " << *args->HOME_PATH << std::endl;
    std::cout << "disable atrc warnings: " << args->disable_atrc_warnings << std::endl;

    // Clean up
    // cleanup();
}