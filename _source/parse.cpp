#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "battosh.hxx"
#include "./commands/commands.hxx"

// .\build_n_run.bat .\win\test.bat -sw -sc

void to_the_end(int command, std::vector<Token> *tokens, size_t &i, Token &token, std::vector<ParsedToken> *parsed_tokens){
    ParsedToken parsed_token;
    parsed_token.command = command;
    parsed_token.value = token.value;
    parsed_token.line = token.line;
    parsed_token.column = token.column;
    i++; // Move to the next token
    bool endline = false;
    for(std::string &flag : token.flags){
        std::cout << "Flag: " << flag << std::endl;
        parsed_token.flags.push_back(flag);
    }
    while (i < tokens->size()) {
        Token next_token = tokens->at(i);
        if (next_token.command == ENDLINE) {
            endline = true;
            parsed_tokens->push_back(parsed_token);
            break;
        } else {
            parsed_token.values.push_back(next_token.value);
        }
        i++; // Move to the next token
    }
    if(!endline){
        parsed_tokens->push_back(parsed_token);
    }
}

void add_single_token(Token &token, int command, std::vector<ParsedToken> *parsed_tokens, size_t &i){
    ParsedToken parsed_token;
    parsed_token.command = command;
    parsed_token.value = token.value;
    parsed_token.line = token.line;
    parsed_token.column = token.column;
    parsed_tokens->push_back(parsed_token);
    i++;
}

std::vector<ParsedToken>* parse(std::vector<Token> *tokens, battosh_info *args){
    std::vector<ParsedToken> *parsed_tokens = new std::vector<ParsedToken>();
    std::cout << "Parsing tokens... \n";
    for(Token &token : *tokens){
        std::cout << "Command: " << token.command << " Value: '" << token.value << "' Line: " << token.line << " Column: " << token.column << std::endl;
        for(std::string &flag : token.flags){
            std::cout << "  Flag: " << flag << std::endl;
        }
    }

    size_t i = 0;
    while (i < tokens->size()) {
        std::cout << "Parsing token: " << i << std::endl;
        Token token = tokens->at(i);
        std::cout << "Command: " << token.command << " Value: '" << token.value << "' Line: " << token.line << " Column: " << token.column << std::endl;
        switch (token.command) {
            case ECHO: {
                to_the_end(ECHO, tokens, i, token, parsed_tokens);
                break;
            }
            case VER: {
                std::cout << "VER" << std::endl;
                add_single_token(token, VER, parsed_tokens, i);
                break;
            }
            case CLS:{
                std::cout << "CLS" << std::endl;
                add_single_token(token, CLS, parsed_tokens, i);
                break;
            }
            case REM: {
                if(args->savecomments) {
                    to_the_end(REM, tokens, i, token, parsed_tokens);
                }
                else {
                    i++;
                }
                break;
            }
            
            case ENDLINE:
                {
                add_single_token(token, ENDLINE, parsed_tokens, i);
                break;
                }
            default:
                i++;
                break;
        }
    }

    return parsed_tokens;
}