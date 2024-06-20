#include "ATRC_VALUES.hxx"
#include "../extern_dependencies/ATRC/include/ATRC.h"
#include "battosh.hxx"
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

void ReadATRC_VALUES(battosh_info *args) {
    std::string home_dir = *args->HOME_PATH;
    std::string atrc_path = home_dir;
#ifdef _WIN32
    atrc_path += "\\battosh\\ATRC\\";
#elif __linux__
    atrc_path += "/battosh/ATRC/";
#endif

    std::string now_reading = "";
    snw("ECHO.atrc", now_reading, atrc_path);
    ATRCFiledata* temp = nullptr;
    try {
        temp = Read(now_reading, "utf-8");
    } catch (std::exception& e) {
        if(!args->disable_atrc_warnings)
            std::cerr << e.what() << std::endl;
    }
    fd_echo = std::unique_ptr<ATRCFiledata>(temp);

    snw("COMMENTS.atrc", now_reading, atrc_path);
    try {
    temp = Read(now_reading, "utf-8");
    } catch (std::exception& e){
        if(!args->disable_atrc_warnings)
            std::cerr << e.what() << std::endl;
    }
    fd_comment = std::unique_ptr<ATRCFiledata>(temp);
}
