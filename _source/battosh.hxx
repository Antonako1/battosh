#ifndef battosh_H
#define battosh_H

#define MAJOR_VERSION 0
#define MINOR_VERSION 0
#define PATCH_VERSION 1

#include <string>
#include <vector>
#include <memory>

#define FL_FLAG_BATTOSH     0

#define HELP_               1
#define VERSION_            2

void message(std::string &msg, int flag, int command, bool error, int line, int column);


struct Token{
    int command;
    std::unique_ptr<std::string> value;
    std::vector<std::string> flags;
    int line;
    int column;
};



extern std::vector<Token> tokens;
struct battosh_info {
    std::unique_ptr<std::string> INPUT_FILE;
    std::unique_ptr<std::string> OUTPUT_FILE;
    bool wsl;
    bool linux;
};
std::vector<Token>* lexical(battosh_info *args);

#endif // battosh_H