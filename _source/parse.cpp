#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "battosh.hxx"
#include "./commands/commands.hxx"

// .\build_n_run.bat .\win\test.bat -sw -sc

void parse_to_the_end(int command, std::vector<Token> *tokens, size_t &i, Token &token, std::vector<ParsedToken> *parsed_tokens){
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
    std::cout << "\nParsing tokens... \n";

    size_t i = 0;
    while (i < tokens->size()) {
        Token token = tokens->at(i);
        std::cout << "Command: " << token.command << " Value: '" << token.value << "' Line: " << token.line << " Column: " << token.column << std::endl;
        for(std::string &flag : token.flags){
            std::cout << "  Flag: " << flag << std::endl;
        }
        
        switch (token.command) {
            case ECHO: {
                parse_to_the_end(ECHO, tokens, i, token, parsed_tokens);
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
                    parse_to_the_end(REM, tokens, i, token, parsed_tokens);
                }
                else {
                    i++;
                }
                break;
            }
            case CALL: {
                parse_to_the_end(CALL, tokens, i, token, parsed_tokens);
                break;
            }
            case TYPE: {
                parse_to_the_end(TYPE, tokens, i, token, parsed_tokens);
                break;
            }
            case CHDIR:
            case CD: {
                parse_to_the_end(CD, tokens, i, token, parsed_tokens);
                break;
            }
            case EXIT: {
                parse_to_the_end(EXIT, tokens, i, token, parsed_tokens);
                break;
            }
            case ENDLINE: {
                add_single_token(token, ENDLINE, parsed_tokens, i);
                break;
            }
            case IF: {
                add_single_token(token, IF, parsed_tokens, i);
                break;
            }
            case ELSE: {
                add_single_token(token, ELSE, parsed_tokens, i);
                break;
            }
            case ELSEIF: {
                add_single_token(token, ELSEIF, parsed_tokens, i);
                break;
            }
            case LPAREN: {
                std::cout << "LPAREN" << std::endl;
                add_single_token(token, LPAREN, parsed_tokens, i);
                break;
            }
            case RPAREN: {
                std::cout << "RPAREN" << std::endl;
                add_single_token(token, RPAREN, parsed_tokens, i);
                break;
            }
            case EXIST: {
                add_single_token(token, EXIST, parsed_tokens, i);
                break;
            }
            case EQU:
                add_single_token(token, EQU, parsed_tokens, i);
                break;
            case NEQ:
                add_single_token(token, NEQ, parsed_tokens, i);
                break;
            case LSS:
                add_single_token(token, LSS, parsed_tokens, i);
                break;
            case LEQ:
                add_single_token(token, LEQ, parsed_tokens, i);
                break;
            case GTR:
                add_single_token(token, GTR, parsed_tokens, i);
                break;
            case GEQ:
                add_single_token(token, GEQ, parsed_tokens, i);
                break;
            case AND:
                add_single_token(token, AND, parsed_tokens, i);
                break;
            case OR:
                add_single_token(token, OR, parsed_tokens, i);
                break;
            case NOT:
                add_single_token(token, NOT, parsed_tokens, i);
                break;
            case XOR:
                add_single_token(token, XOR, parsed_tokens, i);
                break;
            case SHL:
                add_single_token(token, SHL, parsed_tokens, i);
                break;
            case SHR:
                add_single_token(token, SHR, parsed_tokens, i);
                break;
            case MKDIR:
                parse_to_the_end(MKDIR, tokens, i, token, parsed_tokens);
                break;
            case ECHOOFF:
                parse_to_the_end(ECHOOFF, tokens, i, token, parsed_tokens);
                break;
            default:
                add_single_token(token, UNKNOWN, parsed_tokens, i);
                break;
        }
    }

    return parsed_tokens;
}