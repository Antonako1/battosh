#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "battosh.hxx"
#include "./commands/commands.hxx"

void parse_to_the_end(int command, std::vector<Token> *tokens, size_t &i, Token &token, std::vector<ParsedToken> *parsed_tokens){
    ParsedToken parsed_token;
    parsed_token.command = command;
    parsed_token.value = token.value;
    parsed_token.line = token.line;
    parsed_token.column = token.column;
    i++;
    bool endline = false;
    for(std::string &flag : token.flags){
        std::string temp = flag;
        for(char &c : temp){
            c = toupper(c);
        }
        parsed_token.flags.push_back(temp);
    }
    for(std::string &attribute : token.attributes){
        std::string temp = attribute;
        for(char &c : temp){
            c = toupper(c);
        }
        parsed_token.attributes.push_back(temp);
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
        i++; 
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
    // parsed_token.flags = token.flags;
    parsed_tokens->push_back(parsed_token);
    i++;
}

std::vector<ParsedToken>* parse(std::vector<Token> *tokens, battosh_info *args){
    std::vector<ParsedToken> *parsed_tokens = new std::vector<ParsedToken>();

    size_t i = 0;
    while (i < tokens->size()) {
        Token token = tokens->at(i);    
        switch (token.command) {
            case REM: {
                if(args->no_comments) {
                    parse_to_the_end(NULL__TOKEN, tokens, i, token, parsed_tokens);
                }
                else {
                    parse_to_the_end(REM, tokens, i, token, parsed_tokens);
                }
                break;
            }

            // parse to the end stack
            case DIR:
            case ECHO:
            case CALL:
            case TYPE:
            case MKDIR:
            case MD:
            case CHDIR:
            case CD:
            case CDBACK:
            case RD:
            case RMDIR:
            case REN:
            case RENAME:
            case TIMEOUT:
            case ECHOOFF:
            case SET:
            case MOVE:
            case EXIT:
            case HELP:
                parse_to_the_end(token.command, tokens, i, token, parsed_tokens);
                break;

            // add single token stack
            case PAUSE:
            case CLS:
            case VER:
            case ECHO_emptyline:
            case ENDLINE:
            case IF:        // TODO, NOTE: /I will not propably work, add_single_token should add flags
            case ELSE:
            case ELSEIF:
            case VAR:
            case VARARG:
            case TILDEARG:
            case COLONTILDEARG:
            case FORVAR:
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
            // case XOR:
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
