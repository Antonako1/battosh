#pragma once
#include <cstdlib>
#include <string>
#include <memory>
#include <stdexcept>
#include "../extern_dependencies/ATRC/include/ATRC.h"
#include "battosh.hxx"

void ReadATRC_VALUES(battosh_info *args);

extern std::unique_ptr<ATRCFiledata> fd_echo;
extern std::unique_ptr<ATRCFiledata> fd_comment;

inline std::string get_home_dir(std::string homePath_arg = "") {

    char* homePath = nullptr;
    std::string homeDir;
#ifdef _WIN32
    size_t len;
    _dupenv_s(&homePath, &len, "USERPROFILE");
    homeDir = homePath ? std::string(homePath) : "";
    free(homePath);
#elif __linux__
    homePath = getenv("HOME");
    homeDir = homePath ? std::string(homePath) : "";
#endif
    if(homeDir == "")
        throw std::runtime_error("Could not get home directory, please set the HOME flag.");
    return homeDir;
}

void cleanup();