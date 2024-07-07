#pragma once
#include <cstdlib>
#include <string>
#include <memory>
#include <stdexcept>
#include "../extern_dependencies/ATRC/include/ATRC.h"
#include "battosh.hxx"

void ReadATRC_VALUES(battosh_info *args);


extern std::unique_ptr<ATRCFiledata> fd_battosh;

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
extern std::unique_ptr<ATRCFiledata> fd_if;
extern std::unique_ptr<ATRCFiledata> fd_mkdir;
extern std::unique_ptr<ATRCFiledata> fd_rmdir;
extern std::unique_ptr<ATRCFiledata> fd_dir;
extern std::unique_ptr<ATRCFiledata> fd_set;
extern std::unique_ptr<ATRCFiledata> fd_copy;
extern std::unique_ptr<ATRCFiledata> fd_help;
extern std::unique_ptr<ATRCFiledata> fd_move;
extern std::unique_ptr<ATRCFiledata> fd_pause;
extern std::unique_ptr<ATRCFiledata> fd_rename;
extern std::unique_ptr<ATRCFiledata> fd_timeout;
extern std::unique_ptr<ATRCFiledata> fd_string_operators;
extern std::unique_ptr<ATRCFiledata> fd_process_flags;
extern std::unique_ptr<ATRCFiledata> fd_logical_operators;
extern std::unique_ptr<ATRCFiledata> fd_arithmetic_operators;
extern std::unique_ptr<ATRCFiledata> fd_assignment_operators;
extern std::unique_ptr<ATRCFiledata> fd_bitwise_operators;

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
