#ifndef battosh_H
#define battosh_H

#define VERSION             "0.0.1"

#include <string>
#include <vector>
#include <memory>

#define FL_FLAG_BATTOSH     0

#define HELP_               1
#define VERSION_            2

void message(std::string &msg, int flag, int command, bool error, int line, int column);


struct Token{
    int command;
    std::string value;
    std::vector<std::string> flags;
    int line;
    int column;
};



extern std::vector<Token> tokens;
struct battosh_info {
    std::unique_ptr<std::string> INPUT_FILE;
    std::unique_ptr<std::string> OUTPUT_FILE;
    bool wsl;
    bool _linux_battosh;
    bool savewhitespace;
    bool savecomments;
};

std::vector<Token>* lexical(battosh_info *args);

struct ParsedToken{
    int command;
    std::string value;

    // inner values, example: echo "hello world"
    std::vector<std::string> values;
    std::vector<std::string> flags;
    int line;
    int column;
};
std::vector<ParsedToken>* parse(std::vector<Token> *tokens, battosh_info *args);


void tosh(std::vector<ParsedToken> *tokens, battosh_info *args);

#endif // battosh_H