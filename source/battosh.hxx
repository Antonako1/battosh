#ifndef BATTOSH_H
#define BATTOSH_H

#include "../extern_dependencies/ATRC/include/ATRC.h"

#ifdef DEBUG
    #include <iostream>
    const bool not___defined___ = bool( std::cout << "%%%DEBUG MODE%%%" << std::endl );
#endif

#define VERSION             "0.1.0"

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
    std::vector<std::string> flags;         
    std::vector<std::string> attributes;    
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
    bool batchtoshell; // TODO turn .bat to .sh
    std::unique_ptr<std::string> HOME_PATH; // Path to user's home folder. WIN: %HOMEPATH% LINUX: ~/.config
    bool disable_atrc_warnings;
};

std::vector<Token>* lexical(battosh_info *args);

struct ParsedToken{
    int command;
    std::string value;
    std::vector<std::string> values;
    std::vector<std::string> flags;
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
std::string &output,
bool daw
);

void read_variable_to_output
(
std::string varname,
std::string original_value,
ATRCFiledata *fd,
std::string &output, 
bool daw
);

void start_output_log(battosh_info *args);
void write_to_output_log(std::string log);
void save_output_log();
#endif // BATTOSH_H

