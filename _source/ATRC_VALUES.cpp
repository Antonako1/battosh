#include "ATRC_VALUES.hxx"
#include "../extern_dependencies/ATRC/include/ATRC.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>

std::unique_ptr<ATRCFiledata> fd_echo;
std::unique_ptr<ATRCFiledata> fd_comment;

void snw(const std::string& file, std::string& nw, const std::string& path) {
    nw = path + file;
}

void ReadATRC_VALUES(const std::string& home_dir) {
    std::string atrc_path = home_dir;
#ifdef _WIN32
    atrc_path += "\\battosh\\ATRC\\";
#elif __linux__
    atrc_path += "/battosh/ATRC/";
#endif

    std::string now_reading = "";
    snw("ECHO.atrc", now_reading, atrc_path);
    ATRCFiledata* temp = Read(now_reading, "utf-8");
    fd_echo = std::unique_ptr<ATRCFiledata>(temp);

    snw("COMMENTS.atrc", now_reading, atrc_path);
    temp = Read(now_reading, "utf-8");
    fd_comment = std::unique_ptr<ATRCFiledata>(temp);
}
