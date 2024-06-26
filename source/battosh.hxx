#ifndef battosh_H
#define battosh_H

#include "../extern_dependencies/ATRC/include/ATRC.h"
// #include "VARIABLES.hxx"

#ifdef DEBUG
    #include <iostream>
    const bool not___defined___ = bool( std::cout << "%%%DEBUG MODE%%%" << std::endl );
#endif

#define VERSION             "0.0.2"

#include <string>
#include <vector>
#include <memory>

#define FL_FLAG_BATTOSH     0
#define FL_FLAG_TOSH       1

#define HELP_               1
#define VERSION_            2
#define ATRC_NOT_FOUND      3

void message(std::string &msg, int flag, int command, bool error, int line, int column);


struct Token{
    int command;
    std::string value;
    std::vector<std::string> flags;         // example: /Q
    std::vector<std::string> attributes;    // example: /A:D
    int line;
    int column;
};



extern std::vector<Token> tokens;
struct battosh_info {
    std::unique_ptr<std::string> INPUT_FILE;
    std::unique_ptr<std::string> OUTPUT_FILE;
    bool wsl;
    bool no_linux;
    bool no_whitespace;
    bool no_comments;
    std::unique_ptr<std::string> SHELL;
    bool mkdir_p;
    bool quiet;
    bool dirsort;
    bool batchtoshell; // turn .bat to .sh
    std::unique_ptr<std::string> HOME_PATH;
    bool disable_atrc_warnings;
};

std::vector<Token>* lexical(battosh_info *args);

struct ParsedToken{
    int command;
    std::string value;

    // inner values, example: echo "hello world"
    std::vector<std::string> values;
    // flags, example: /Q
    std::vector<std::string> flags;
    // attributes, example: /A:D
    std::vector<std::string> attributes;
    int line;
    int column;
};
std::vector<ParsedToken>* parse(std::vector<Token> *tokens, battosh_info *args);


void tosh(std::vector<ParsedToken> *tokens, battosh_info *args);

void pathing(std::string &input, battosh_info *args);

void read_key_to_output(
    std::string block,
    std::string key,
    std::string original_value,
    ATRCFiledata *fd,
    std::string &cts,
    std::string &output,
    bool daw
    );

#endif // battosh_H
