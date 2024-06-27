#pragma once
#include <cstdlib>
#include <string>
#include <memory>
#include <stdexcept>
#include "../extern_dependencies/ATRC/include/ATRC.h"
#include "battosh.hxx"

void ReadATRC_VALUES(battosh_info *args);


extern std::unique_ptr<ATRCFiledata> fd_variables;
extern std::unique_ptr<ATRCFiledata> fd_echo;
extern std::unique_ptr<ATRCFiledata> fd_comment;
extern std::unique_ptr<ATRCFiledata> fd_ver;
extern std::unique_ptr<ATRCFiledata> fd_cls;
extern std::unique_ptr<ATRCFiledata> fd_call;
extern std::unique_ptr<ATRCFiledata> fd_type;
extern std::unique_ptr<ATRCFiledata> fd_cd;
extern std::unique_ptr<ATRCFiledata> fd_exit;
extern std::unique_ptr<ATRCFiledata> fd_relational_operators;
//
//
//
//
extern std::unique_ptr<ATRCFiledata> fd_if;
extern std::unique_ptr<ATRCFiledata> fd_mkdir;
extern std::unique_ptr<ATRCFiledata> fd_rmdir;
extern std::unique_ptr<ATRCFiledata> fd_set;

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
    if(homeDir != ""){
        homeDir += "/.config/";
    }
#endif
    if(homeDir == "")
        throw std::runtime_error("Could not get home directory, please set the HOME flag.");
    return homeDir;
}

// void cleanup();
