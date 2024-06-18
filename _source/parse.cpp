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
x
    size_t i = 0;
    while (i < tokens->size()) {
        Token token = tokens->at(i);        
        switch (token.command) {
            case REM: {
                if(args->savecomments) {
                    parse_to_the_end(REM, tokens, i, token, parsed_tokens);
                }
                else {
                    i++;
                }
                break;
            }

            // parse to the end stack
            case ECHO:
            case CALL:
            case TYPE:
            case MKDIR:
            case CHDIR:
            case CD:
                parse_to_the_end(token.command, tokens, i, token, parsed_tokens);
                break;

            // add single token stack
            case CLS:
            case VER:
            case EXIT:
            case ENDLINE:
            case IF:
            case ELSE:
            case ELSEIF:
            case LPAREN:
            case RPAREN:
            case EXIST:
            case EQU:
            case NEQ:
            case LSS:
            case LEQ:
            case GTR:
            case GEQ:
            case AND:
            case OR:
            case NOT:
            case XOR:
            case SHL:
            case SHR:
                add_single_token(token, token.command, parsed_tokens, i);
                break;
            default:
                add_single_token(token, UNKNOWN, parsed_tokens, i);
                break;
        }
    }

    return parsed_tokens;
}