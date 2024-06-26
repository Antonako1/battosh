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
#include "VARIABLES.hxx"

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
SET_FLAG set_flag;

void send_message(std::string msg, int errnum, bool disable_atrc_warnings){
    if(errnum == ATRC_NOT_FOUND && disable_atrc_warnings){
        return;
    }
    message(msg, FL_FLAG_TOSH, 
    errnum, false, -1,-1);
}
void read_key_to_output
    (
    std::string block, 
    std::string key,
    std::string original_value,
    ATRCFiledata *fd,
    std::string &cts, 
    std::string &output, 
    bool daw
    )
{
    cts = "";    
    ReadKey(fd, block, key, cts);
    if(cts == ""){
        if(!DoesExistKey(fd, block, key)){
            send_message("block: ["+block+"] key: <"+key+"> not found", ATRC_NOT_FOUND, daw);
        }
        output += original_value;
    } else {
        output += cts;
    }   
}

void add_end_values(ParsedToken &parsed_token, std::string &output, battosh_info *args){	
	// std::string temp_buffer = "";
    std::string temp_output = output;
    for(std::string value : parsed_token.values){
        // temp_buffer += value + " ";
        temp_output += value + " ";
    }
	
	variablify(temp_output, args);
	pathing(temp_output, args);
	// variablify(temp_buffer, args);
	// pathing(temp_buffer, args);
    // temp_output += temp_buffer;
	output = temp_output;

}

std::string add_end_values_as_string(ParsedToken &parsed_token, battosh_info *args){
    std::string output = "";
    add_end_values(parsed_token, output, args);
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
            // read_key_to_output(cts1, output, "RELATIONAL_OPERATORS", "EQU", fd_relational_operators.get(), "-eq ", daw);
            read_key_to_output("RELATIONAL_OPERATORS", "EQU", "-eq ", fd_relational_operators.get(), cts1, output, daw);
            break;
        case NEQ:
            read_key_to_output("RELATIONAL_OPERATORS", "NEQ", "-ne ", fd_relational_operators.get(), cts1, output, daw);
            break;
        case LSS:
            read_key_to_output("RELATIONAL_OPERATORS", "LSS", "-lt ", fd_relational_operators.get(), cts1, output, daw);
            break;
        case LEQ:
            read_key_to_output("RELATIONAL_OPERATORS", "LEQ", "-le ", fd_relational_operators.get(), cts1, output, daw);
            break;
        case GTR:
            read_key_to_output("RELATIONAL_OPERATORS", "GTR", "-gt ", fd_relational_operators.get(), cts1, output, daw);
            break;
        case GEQ:
            read_key_to_output("RELATIONAL_OPERATORS", "GEQ", "-ge ", fd_relational_operators.get(), cts1, output, daw);
            break;
        case AND:
            output += "&& ";
            break;
        case OR:
            output += "|| ";
            break;
        case EXIST:
            output += "-e ";
            // expect a file
            // TODO PATH CHECK
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
#ifdef DEBUG
        std::cout << "Token: " << parsed_token.value << " Command: " << parsed_token.command << std::endl;
        for(const auto &flag : parsed_token.flags){
            std::cout << "  Flag: '" << flag << "'" << std::endl;
        }
        for (const auto &value : parsed_token.values) {
            std::cout << "  Value: '" << value << "'" << std::endl;
        }
        for (const auto &attribute : parsed_token.attributes) {
            std::cout << "  Attribute: '" << attribute << "'" << std::endl;
        }
#endif
        if(inside_if || short_hand_if_statement != 0){
            output += std::string(if_statement_intend, ' ');
        }
        cts1 = ""; cts2 = "";
        switch(parsed_token.command){
            case ECHO: {                
                bool updated_path = false;
                for(const auto &flag : parsed_token.flags){
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
                    read_key_to_output("ECHO", "command", "echo ", fd_echo.get(), cts1, output, daw);
                }
                add_end_values(parsed_token, output, args);
                break;
            }
            case CLS: {
                read_key_to_output("CLS", "command", "clear", fd_cls.get(), cts1, output, daw);
                break;
            }
            case VER: {
                read_key_to_output("VER", "command", "uname -r", fd_ver.get(), cts1, output, daw);
                break;
            }
            case CALL:{
                // TODO PATH CHECK
                read_key_to_output("CALL", "command", "source ", fd_call.get(), cts1, output, daw);
                add_end_values(parsed_token, output, args);
                break;
            }
            case TYPE: {
                read_key_to_output("TYPE", "command", "cat ", fd_type.get(), cts1, output, daw);
                // TODO PATH CHECK
                add_end_values(parsed_token, output, args);
                break;
            }
            case CDBACK:
                read_key_to_output("CD", "back", "cd ..", fd_cd.get(), cts1, output, daw);
                break;
            case ECHO_emptyline:
                read_key_to_output("ECHO", "command", "echo ", fd_echo.get(), cts1, output, daw);
                read_key_to_output("ECHO", "blank_line", echo_flag.LINUX_NEWLINE + " ", fd_echo.get(), cts2, output, daw);
                break;
            case CHDIR:
            case CD: {
                buffer = "";
                read_key_to_output("CD", "command", "cd %*% ", fd_cd.get(), cts1, buffer, daw);
                std::vector<std::string> temp = {add_end_values_as_string(parsed_token, args)};
                InsertVar(buffer, temp, fd_cd.get());
                output += buffer;
                break;
            }
            case ECHOOFF: {
                std::string temp = parsed_token.values[0];
                std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
                if(temp == "off"){
                    read_key_to_output("ECHO", "off", "set +x", fd_echo.get(), cts1, output, daw);
                } else {
                    read_key_to_output("ECHO", "on", "set -x", fd_echo.get(), cts1, output, daw);
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
            case SET: {
                std::string temp_buffer = "";
                std::string inner = add_end_values_as_string(parsed_token, args);
                size_t equ_pos = inner.find_first_of('=');
                if(equ_pos == std::string::npos){
                    // TODO error message
                    std::cout << "Invalid variable declaration\n";
                    break;
                }
                std::string var_name = "";
                std::string value = "";

                try{
                    var_name = inner.substr(0, equ_pos);
                } catch(...){
                    var_name = "";
                }

                try{
                    value = inner.substr(equ_pos+1);
                    value = value.substr(0, value.size() - 1);
                } catch(...){
                    value = "";
                }

                if(value.size() < 1){
                    value = " ";        
                }
                if(var_name.size() < 1){
                    var_name = " ";                
                }

                
                if(var_name[0] == '"' && value[value.size()-1] == '"'){
                    var_name = var_name.substr(1, var_name.size()-1);
                    value = value.substr(0, value.size()-1);
                }

                bool flagged = false;
                std::vector<std::string> inserts__ = {var_name, value};
                for(const auto &flag : parsed_token.flags){
                    if(!flagged && flag == set_flag.declare_int){
                        read_key_to_output("SET", "integer", set_flag.linux_int, fd_set.get(), cts1, temp_buffer, daw);
                        flagged = true;
                    } else if (!flagged && flag == set_flag.declare_prompt){
                        read_key_to_output("SET", "prompt", set_flag.linux_int, fd_set.get(), cts1, temp_buffer, daw);
                        flagged = true;
                    }
                }
                if(!flagged){
                    read_key_to_output("SET", "command", set_flag.linux_int, fd_set.get(), cts1, temp_buffer, daw);
                }
                InsertVar(temp_buffer, inserts__, fd_set.get());
                output += temp_buffer;
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
                add_end_values(parsed_token, output, args);
                break;
            }
            case REM: {
                read_key_to_output("COMMENT", "command", "# ", fd_comment.get(), cts1, output, daw);
                add_end_values(parsed_token, output, args);
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
                add_end_values(parsed_token, output, args);
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
                add_end_values(parsed_token, output, args);
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
                    output += "\n"; // !temporary fix
                    output += "fi\n";
                    inside_if = false;
                }
                break;
            }
            case EXIT: {
                read_key_to_output("EXIT", "command", "exit ", fd_exit.get(), cts1, output, daw);
                bool num_provided = false;
                for(const auto &flag : parsed_token.flags){
                    if(flag == exit_flag.EXIT_CURRENT_BATCH){
                        read_key_to_output("EXIT", "errcode", exit_flag.LINUX_EXIT_CURRENT_BATCH, fd_exit.get(), cts1, output, daw);
                        output += parsed_token.values.at(0);
                        num_provided = true;
                    }
                    else if(flag == exit_flag.GET_HELP){
                        read_key_to_output("EXIT", "get_help", exit_flag.LINUX_GET_HELP + " ", fd_exit.get(), cts1, output, daw);
                    }
                }
                if(!num_provided){
                    add_end_values(parsed_token, output, args);
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
                        read_key_to_output("RMDIR", "command", "rmdir ", fd_rmdir.get(), cts1, output, daw);
                        read_key_to_output("RMDIR", "get_help", rmdir_flag.LINUX_GET_HELP + " ", fd_rmdir.get(), cts1, output, daw);
                        updated_command = true;
                        continue;
                    } else if(flag == rmdir_flag.REMOVE_DIR_TREE){
                        if(!updated_command) {
                            read_key_to_output("RMDIR", "modified_command", "rmdir ", fd_rmdir.get(), cts1, output, daw);
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
                    read_key_to_output("RMDIR", "remove_dir_tree_force", rmdir_flag.LINUX_REMOVE_DIR_TREE_FORCE + " ", fd_rmdir.get(), cts1, output, daw);
                } else if (!add_quiet_mode && add_force_mode){
                    read_key_to_output("RMDIR", "remove_dir_tree", rmdir_flag.LINUX_REMOVE_DIR_TREE + " ", fd_rmdir.get(), cts1, output, daw);
                }
                add_end_values(parsed_token, output, args);
                if(add_quiet_mode){
                    output += QUIET_MODE;
                }
                break;
            }
            case MD:
            case MKDIR: {
                // TODO PATH CHECK
                read_key_to_output("MKDIR", "command", "mkdir ", fd_mkdir.get(), cts1, output, daw);
                if(args->mkdir_p){
                    read_key_to_output("MKDIR", "mkdir_p", "mkdir -p ", fd_mkdir.get(), cts1, output, daw);
                }
                for(const auto &flag : parsed_token.flags){
                    if(flag == mkdir_flag.GET_HELP){
                        read_key_to_output("MKDIR", "get_help", mkdir_flag.LINUX_GET_HELP + " ", fd_mkdir.get(), cts1, output, daw);
                    }
                }
                add_end_values(parsed_token, output, args);
                break;
            }
            case UNKNOWN:{
                // std::string temp = add_end_values_as_string(parsed_token, args);
                output += parsed_token.value + " ";
                add_end_values(parsed_token, output, args);
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
                add_end_values(parsed_token, output, args);
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
        while (true) {
            std::cout << "Print the generated script into console? (y/n): ";
            char ans;
            std::cin >> ans;
            if (ans == 'y' || ans == 'Y') {
                std::cout << output << std::endl;
                break;
            } else if (ans == 'n' || ans == 'N') {
                break;
            } else {
                std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
            }
        }
        exit(1);
    }
    file << output;
    file.close();
    // create message()
    std::cout << "File created: " << *args->OUTPUT_FILE << std::endl;
    std::cout << "Ran with flags:" << std::endl;

    if(args->wsl)std::cout << "wsl paths" << std::endl;
    if(args->no_linux)std::cout << "no linux paths" << std::endl;
    if(args->no_whitespace)std::cout << "don't save whitespace" << std::endl;
    if(args->no_comments)std::cout << "don't save comments" << std::endl;
    if(args->SHELL)std::cout << "shell" << std::endl;
    if(args->mkdir_p)std::cout << "mkdir_p" << std::endl;
    if(args->quiet)std::cout << "quiet" << std::endl;
    if(args->dirsort)std::cout << "dirsort" << std::endl;
    if(args->batchtoshell)std::cout << "batchtoshell" << std::endl;
    if(args->HOME_PATH)std::cout << "home path" << std::endl;
    if(args->disable_atrc_warnings)std::cout << "disable atrc warnings" << std::endl;

    // Clean up
    // cleanup();
}
