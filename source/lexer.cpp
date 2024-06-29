#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include "battosh.hxx"
#include "./commands/commands.hxx"

std::string commands[] = {
"VER",          std::to_string(VER),
"ASSOC",        std::to_string(ASSOC),
"BREAK",        std::to_string(BREAK),
"CD",           std::to_string(CD),
"CD..",         std::to_string(CDBACK),
"CHDIR",        std::to_string(CHDIR),
"CLS",          std::to_string(CLS),
"COPY",         std::to_string(COPY),
"DEL",          std::to_string(DEL),
"ERASE",        std::to_string(ERASE),
"DIR",          std::to_string(DIR),
"DATE",         std::to_string(DATE),
"ECHO",         std::to_string(ECHO),
"@ECHO",        std::to_string(ECHOOFF),
"EXIT",         std::to_string(EXIT),
"MD",           std::to_string(MD),
"MKDIR",        std::to_string(MKDIR),
"MOVE",         std::to_string(MOVE),
"PATH",         std::to_string(PATH),
"PAUSE",        std::to_string(PAUSE),
"PROMPT",       std::to_string(PROMPT),
"RD",           std::to_string(RD),
"RMDIR",        std::to_string(RMDIR),
"REN",          std::to_string(REN),
"RENAME",       std::to_string(RENAME),
"REM",          std::to_string(REM),
"@REM",         std::to_string(REM),
"::",           std::to_string(REM),
"START",        std::to_string(START),
"TIME",         std::to_string(TIME),
"TYPE",         std::to_string(TYPE),
"VOL",          std::to_string(VOL),
"ATTRIB",       std::to_string(ATTRIB),
"CHKDSK",       std::to_string(CHKDSK),
"CHOICE",       std::to_string(CHOICE),
"CMD",          std::to_string(CMD),
"COMP",         std::to_string(COMP),
"CONVERT",      std::to_string(CONVERT),
"DRIVEQUERY",   std::to_string(DRIVEQUERY),
"EXPAND",       std::to_string(EXPAND),
"FIND",         std::to_string(FIND),
"FORMAT",       std::to_string(FORMAT),
"HELP",         std::to_string(HELP),
"IPCONFIG",     std::to_string(IPCONFIG),
"LABEL",        std::to_string(LABEL),
"MORE",         std::to_string(MORE),
"NET",          std::to_string(NET),
"PING",         std::to_string(PING),
"SHUTDOWN",     std::to_string(SHUTDOWN),
"SORT",         std::to_string(SORT),
"SUBST",        std::to_string(SUBST),
"SYSTEMINFO",   std::to_string(SYSTEMINFO),
"TASKKILL",     std::to_string(TASKKILL),
"TASKLIST",     std::to_string(TASKLIST),
"XCOPY",        std::to_string(XCOPY),
"TREE",         std::to_string(TREE),
"FC",           std::to_string(FC),
"DISKPART",     std::to_string(DISKPART),
"TITLE",        std::to_string(TITLE),
"SET",          std::to_string(SET),
"IF",           std::to_string(IF),
"ELSE",         std::to_string(ELSE),
"ELSEIF",       std::to_string(ELSEIF),
"FOR",          std::to_string(FOR),
"GOTO",         std::to_string(GOTO),
"CALL",         std::to_string(CALL),
"SHIFT",        std::to_string(SHIFT),
"SETLOCAL",     std::to_string(SETLOCAL),
"ENDLOCAL",     std::to_string(ENDLOCAL),
"FINDSTR",      std::to_string(FINDSTR),
"TIMEOUT",      std::to_string(TIMEOUT),
"SCHTASKS",     std::to_string(SCHTASKS),
"WMIC",         std::to_string(WMIC),
"SC",           std::to_string(SC),
"REG",          std::to_string(REG),
"POWERCFG",     std::to_string(POWERCFG),
"BITSADMIN",    std::to_string(BITSADMIN),
"CIPHER",       std::to_string(CIPHER),
"COMPACT",      std::to_string(COMPACT),
"DISKCOMP",     std::to_string(DISKCOMP),
"DISKCOPY",     std::to_string(DISKCOPY),
"DRIVERQUERY",  std::to_string(DRIVERQUERY),
"FSUTIL",       std::to_string(FSUTIL),
"GPRESULT",     std::to_string(GPRESULT),
"LOGMAN",       std::to_string(LOGMAN),
"FLAG",         std::to_string(FLAG),
"VAR",          std::to_string(VAR),
"SETX",         std::to_string(SETX),
"(",            std::to_string(LPAREN),
")",            std::to_string(RPAREN),
"EQU",          std::to_string(EQU),
"NEQ",          std::to_string(NEQ),
"LSS",          std::to_string(LSS),
"LEQ",          std::to_string(LEQ),
"GTR",          std::to_string(GTR),
"GEQ",          std::to_string(GEQ),
"AND",          std::to_string(AND),
"OR",           std::to_string(OR),
"NOT",          std::to_string(NOT),
"SHL",          std::to_string(SHL),
"SHR",          std::to_string(SHR),
"EXIST",        std::to_string(EXIST),
"EQU",           std::to_string(EQU),
"NEQ",           std::to_string(NEQ),
"LSS",            std::to_string(LSS),
"LEQ",           std::to_string(LEQ),
"GTR",            std::to_string(GTR),
"GEQ",           std::to_string(GEQ),
"&&",           std::to_string(AND),
"||",           std::to_string(OR),
"!",            std::to_string(NOT),
};

std::string look_ahead(size_t &index, const std::string &line) {
    if (index < line.size()) {
        return line.substr(index, 1);
    }
    return "";
}
void consume(size_t &index, const std::string &line, std::string &buffer) {
    if (index < line.size()) {
        buffer += line[index];
        index++;
    }
}


int get_command(std::string command) {
    for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i += 2) {
        if (commands[i] == command) {
            return std::stoi(commands[i + 1]);
        }
    }
    return -1;
}


void add_token(std::vector<Token> *tokens, std::string &buffer, int line, int column, int extra = -1) {
    Token _token;
    if(extra == -1){
        std::string newstr = buffer;
        std::transform(newstr.begin(), newstr.end(), newstr.begin(), ::toupper);
        _token.command = get_command(newstr);
        if (_token.command == -1) {
            _token.command = UNKNOWN;
        }
    } else {
        _token.command = extra;
    }
    _token.value = std::string(buffer);
    _token.line = line;
    _token.column = column;
    tokens->push_back(_token);
    buffer.clear();
}

bool add_echo_new_line(std::vector<Token> *tokens, std::string &buffer, int line_num, int column_num){
    if(buffer.length() > 4){
        // bad bad bad
        std::string temp = buffer;
        std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        if(temp.substr(0, 4) == "ECHO" 
        && (
            temp.substr(4,5) == "."
            ||temp.substr(4,5) == "("
            ||temp.substr(4,5) == "+"
            ||temp.substr(4,5) == ","
            ||temp.substr(4,5) == ";"
            ||temp.substr(4,5) == ":"
        )
        ) {
            add_token(tokens, buffer, line_num, column_num, ECHO_emptyline);
            return true;
        }
    }
    return false;
}

std::vector<Token>* lexical(battosh_info *args) {
    std::string input_file = *args->INPUT_FILE;

    std::ifstream file(input_file, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "ERROR OPENING FILE: " << input_file << std::endl;
        exit(1);
    }

    std::vector<Token> *tokens = new std::vector<Token>();
    std::string line;
    int line_num = 1;
    int column_num = 1;

    bool skip = false;

    while (std::getline(file, line)) {
        size_t index = 0;
        std::string buffer;

        for (size_t i = 0; i < line.size(); i++) {
            std::string ahead = look_ahead(index, line);
            switch (ahead[0]) {
// sketchy work for line endings
// ifstream skips last character, which is line feed (0x0A)
// on linux, it will be appended after the line has been read
// Will break if on windows, file ends with only line feed
#ifdef _WIN32
                case '\n':
                case '\r':
                    // std::cout << "line endings" << std::endl;
                    if (!buffer.empty()) {
                        if(!add_echo_new_line(tokens, buffer, line_num, column_num))
                            add_token(tokens, buffer, line_num, column_num, -1);
                    }

                    add_token(tokens, buffer, line_num, column_num, ENDLINE);
                    break;
#endif
                case ' ':
                case '\t':{
                    if (!buffer.empty()) {
                        if(!add_echo_new_line(tokens, buffer, line_num, column_num))
                            add_token(tokens, buffer, line_num, column_num, -1);
                        // add_token(tokens, buffer, line_num, column_num, -1);
                    }
                }
                    break;
                // TODO NOTE WIP
                case '^': {
                    index++;
                    char ahead = look_ahead(index, line)[0];
                    buffer += ahead;
                    break;
                }
                case '"': {
                        buffer += ahead;
                        index++;
                        while (index < line.size()) {
                            if (line[index] == '"') {
                                break;
                            }
                            buffer += line[index];
                            index++;
                        }
                        buffer += '"';

                    }
                    break;
                case ':':{
                    bool is_comment = false;
                    index++;
                    if(look_ahead(index, line) == ":"){
                        if (!buffer.empty()) {
                            add_token(tokens, buffer, line_num, column_num, -1);
                        }
                        
                        // badbadbadx444444444444444444444
                        buffer = "";
                        add_token(tokens, buffer, line_num, column_num, ENDLINE);

                        buffer = "::";
                        add_token(tokens, buffer, line_num, column_num, REM);
                        skip = true;
                        is_comment = true;
                        break;
                    }
                    index--;

                    if(!is_comment){
                        // :DDDDDDDDDD
                        consume(index, line, buffer);
                        consume(index, line, buffer);
                        index--;
                    }
                    break;
                }
                case '@':
                    consume(index, line, buffer);
                    index--;
                    {
                        std::string rem = "";
                        for (size_t i = index; i < line.size(); i++) {
                            rem += std::toupper(line[i]);
                            if (rem == "@REM") {
                                buffer.clear();
                                skip = true;
                                break;
                            }
                        }
                        std::string echo = "";
                        for (size_t i = index; i < line.size(); i++) {
                            echo += std::toupper(line[i]);
                            if (echo == "@ECHO") {
                                skip = true;
                                break;
                            }
                        }
                    // NOTE: test. allow everything to start with @
                    if(!skip){
                        buffer = buffer.substr(0, buffer.size() - 1);
                    }
                    }
                    break;
                case '/':{
                        std::string flag = "/";
                        std::string attribute = ":";
                        size_t flag_index = index + 1;
                        char previous = line[flag_index - 3];
                        if (line[flag_index - 3] != '/' && line[flag_index -2] != ' ') {
                            buffer += "/";
                            break;
                        }
                        bool flag_found = false;
                        while (flag_index < line.size()) {
                            ahead = look_ahead(flag_index, line);
                            if (ahead == " " || ahead == "/" || ahead == "\n" ||
                                ahead == "\r" || ahead == "\t" || ahead == ":" || ahead == "-") {
                                flag_found = true;
                                tokens->at(tokens->size() - 1).flags.push_back(flag);
                                // TODO NOTE: /AD /A:D and /A-D all work
                                if(ahead == ":" || ahead == "-"){
                                    flag_index++;
                                    ahead = look_ahead(flag_index, line);
                                    while (flag_index < line.size()) {
                                        if (ahead == " " || ahead == "/" || ahead == "\n" ||
                                            ahead == "\r" || ahead == "\t") {
                                            break;
                                        }
                                        attribute += ahead;
                                        flag_index++;
                                        ahead = look_ahead(flag_index, line);
                                        tokens->at(tokens->size() - 1).attributes.push_back(attribute);
                                        attribute = ":";
                                    }
                                }
                                break;
                            }
                            flag += ahead;
                            flag_index++;
                        }
                        flag_index--;

                        if(!flag_found){
                            buffer += "/";
                        }

                        index = flag_index;
                    }
                    break;
                default:
                    consume(index, line, buffer);
                    continue;
            }

            index++;
            column_num++;
        }

        if (!buffer.empty()) {
            if(!add_echo_new_line(tokens, buffer, line_num, column_num))
                add_token(tokens, buffer, line_num, column_num, -1);
        }

        #ifdef __linux__ 
        // no can do situation. will break everything about endlines
        add_token(tokens, buffer, line_num, column_num, ENDLINE);
        #endif

        column_num = 1;
        line_num++;
    }

    file.close();

    return tokens;
}