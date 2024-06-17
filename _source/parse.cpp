#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "battosh.hxx"
#include "./commands/commands.hxx"
std::vector<ParsedToken>* parse(std::vector<Token> *tokens, battosh_info *args){
    std::vector<ParsedToken> *parsed_tokens = new std::vector<ParsedToken>();

    size_t i = 0;
    while (i < tokens->size()) {
        Token token = tokens->at(i);
        std::cout << "Command: " << token.command << " Value: '" << token.value << "' Line: " << token.line << " Column: " << token.column << std::endl;
        switch (token.command) {

            case ECHO: {
                std::cout << "Echo command" << std::endl;
                ParsedToken parsed_token;
                parsed_token.command = ECHO;
                parsed_token.value = token.value;
                parsed_token.line = token.line;
                parsed_token.column = token.column;
                std::cout << "Command: " << parsed_token.command << " Value: '" << parsed_token.value <<
                 "' Line: " << parsed_token.line << " Column: " << parsed_token.column << std::endl;
                i++; // Move to the next token after ECHO command
                std::cout << i << " " << tokens->size() << "\n";
                bool endline = false;
                while (i < tokens->size()) {
                    Token next_token = tokens->at(i);
                    if (next_token.command == ENDLINE) {
                        endline = true;
                        std::cout << "Saved echo command" << std::endl;
                        parsed_tokens->push_back(parsed_token);
                        if (args->savewhitespace) {
                            ParsedToken whitespace_token;
                            whitespace_token.command = ENDLINE;
                            whitespace_token.value = next_token.value;
                            whitespace_token.line = next_token.line;
                            whitespace_token.column = next_token.column;
                            parsed_tokens->push_back(whitespace_token);
                        }
                        break;
                    } else {
                        parsed_token.values.push_back(next_token.value);
                    }
                    i++; // Move to the next token
                }
                if(!endline){
                    parsed_tokens->push_back(parsed_token);
                }
                break;
            }
            default:
                // Handle other commands or tokens here if needed
                i++; // Move to the next token
                break;
        }
    }

    return parsed_tokens;
}