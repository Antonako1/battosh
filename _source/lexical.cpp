#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include "battosh.hxx"
#include "./commands/commands.hxx"

std::string commands[] = {
"___",      std::to_string(___),
"VER",      std::to_string(VER),
"ASSOC",    std::to_string(ASSOC),
"CD",       std::to_string(CD),
"CLS",      std::to_string(CLS),
"COPY",     std::to_string(COPY),
"DEL",      std::to_string(DEL),
"DIR",      std::to_string(DIR),
"DATE",     std::to_string(DATE),
"ECHO",     std::to_string(ECHO),
"EXIT",     std::to_string(EXIT),
"MD",       std::to_string(MD),
"MKDIR",    std::to_string(MKDIR),
"MOVE",     std::to_string(MOVE),
"PATH",     std::to_string(PATH),
"PAUSE",    std::to_string(PAUSE),
"PROMPT",   std::to_string(PROMPT),
"RD",       std::to_string(RD),
"RMDIR",    std::to_string(RMDIR),
"REN",      std::to_string(REN),
"REM",      std::to_string(REM),
"START",    std::to_string(START),
"TIME",     std::to_string(TIME),
"TYPE",     std::to_string(TYPE),
"VOL",      std::to_string(VOL),
"ATTRIB",   std::to_string(ATTRIB),
"CHKDSK",   std::to_string(CHKDSK),
"CHOICE",   std::to_string(CHOICE),
"CMD",      std::to_string(CMD),
"COMP",     std::to_string(COMP),
"CONVERT",  std::to_string(CONVERT),
"DRIVEQUERY",   std::to_string(DRIVEQUERY),
"EXPAND",   std::to_string(EXPAND),
"FIND",     std::to_string(FIND),
"FORMAT",   std::to_string(FORMAT),
"HELP",     std::to_string(HELP),
"IPCONFIG", std::to_string(IPCONFIG),
"LABEL",    std::to_string(LABEL),
"MORE",     std::to_string(MORE),
"NET",      std::to_string(NET),
"PING",     std::to_string(PING),
"SHUTDOWN", std::to_string(SHUTDOWN),
"SORT",     std::to_string(SORT),
"SUBST",    std::to_string(SUBST),
"SYSTEMINFO",   std::to_string(SYSTEMINFO),
"TASKKILL", std::to_string(TASKKILL),
"TASKLIST", std::to_string(TASKLIST),
"XCOPY",    std::to_string(XCOPY),
"TREE",     std::to_string(TREE),
"FC",       std::to_string(FC),
"DISKPART", std::to_string(DISKPART),
"TITLE",    std::to_string(TITLE),
"SET",      std::to_string(SET),
"IF",       std::to_string(IF),
"ELSE",     std::to_string(ELSE),
"FOR",      std::to_string(FOR),
"GOTO",     std::to_string(GOTO),
"CALL",     std::to_string(CALL),
"SHIFT",    std::to_string(SHIFT),
"SETLOCAL", std::to_string(SETLOCAL),
"ENDLOCAL", std::to_string(ENDLOCAL),
"FINDSTR",  std::to_string(FINDSTR),
"TIMEOUT",  std::to_string(TIMEOUT),
"SCHTASKS", std::to_string(SCHTASKS),
"WMIC",     std::to_string(WMIC),
"SC",       std::to_string(SC),
"REG",      std::to_string(REG),
"POWERCFG", std::to_string(POWERCFG),
"BITSADMIN",std::to_string(BITSADMIN),
"CIPHER",   std::to_string(CIPHER),
"COMPACT",  std::to_string(COMPACT),
"DISKCOMP", std::to_string(DISKCOMP),
"DISKCOPY", std::to_string(DISKCOPY),
"DRIVERQUERY",  std::to_string(DRIVERQUERY),
"FSUTIL",   std::to_string(FSUTIL),
"GPRESULT", std::to_string(GPRESULT),
"LOGMAN",   std::to_string(LOGMAN),
"FLAG",     std::to_string(FLAG),
"VAR",      std::to_string(VAR),
"SETX",     std::to_string(SETX),
};

std::string look_ahead(size_t &index, const std::string &line) {
    if (index < line.size()) {
        return line.substr(index, 1);
    }
    return "";
}
std::string consume(size_t &index, const std::string &line, std::string &buffer) {
    if (index < line.size()) {
        buffer += line[index];
        index++;
    }
    return buffer;
}


int get_command(std::string command) {
    for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i += 2) {
        if (commands[i] == command) {
            return std::stoi(commands[i + 1]);
        }
    }
    return -1;
}




std::vector<Token>* lexical(battosh_info *args){
    std::cout << *args->INPUT_FILE << std::endl;
    std::string input_file = *args->INPUT_FILE;

    // Replace backslashes with forward slashes
    std::replace(input_file.begin(), input_file.end(), '\\', '/');

    std::ifstream file(input_file, std::ios::in);

    if (!file.is_open()) {
        std::cerr << "ERROR OPENING FILE: " << input_file << std::endl;
        exit(1);
    }

    std::vector<Token> *tokens = new std::vector<Token>();
    std::string line;
    int line_num = 1;
    int column_num = 1;
    // bool breakhere = false;
    while(std::getline(file, line)){
        size_t index = 0;
        std::string buffer;
        while (index < line.size()) {
            std::cout << line[index] << std::endl;
            std::string ahead = look_ahead(index, line);
            switch (ahead[0])
            {
            case ' ':
            case '\t': {
                // Create a token from the buffer
                Token _token;
                // Check if buffer is a command
                _token.command = get_command(buffer);
                if (_token.command == -1) {
                    std::cout << "Invalid command: " << buffer << std::endl;
                    exit(_token.command);
                }
                _token.value = std::make_unique<std::string>(buffer);
                _token.line = line_num;
                _token.column = column_num;
                tokens->push_back(_token);
                buffer.clear();
                index++;
                break;
            }
            case '%':
                // Variable
                break;
            case '"': {
                // String
                break;
            }
            case '/': {
                // Argument to the previous command
                break;
            }
            default:
                // Consume and process characters into tokens
                consume(index, line, buffer);
                // Tokenize buffer (placeholder for actual tokenization logic)
                // Assuming a simple token is created for each buffer
                tokens->emplace_back(Token{ /* Initialize with buffer */ });
                buffer.clear();
                break;
            }
        }
        column_num = 1;
        line_num++;
    }

    return tokens;
}

