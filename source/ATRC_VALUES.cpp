#include "ATRC_VALUES.hxx"
#include "../extern_dependencies/ATRC/include/ATRC.h"
#include "battosh.hxx"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <filesystem>  // For std::filesystem
#include <stdexcept>

namespace fs = std::filesystem;
std::unique_ptr<ATRCFiledata> fd_battosh = nullptr;

std::unique_ptr<ATRCFiledata> fd_variables = nullptr;
std::unique_ptr<ATRCFiledata> fd_echo = nullptr;
std::unique_ptr<ATRCFiledata> fd_comment = nullptr;
std::unique_ptr<ATRCFiledata> fd_ver = nullptr;
std::unique_ptr<ATRCFiledata> fd_cls = nullptr;
std::unique_ptr<ATRCFiledata> fd_call = nullptr;
std::unique_ptr<ATRCFiledata> fd_type = nullptr;
std::unique_ptr<ATRCFiledata> fd_cd = nullptr;
std::unique_ptr<ATRCFiledata> fd_exit = nullptr;
std::unique_ptr<ATRCFiledata> fd_relational_operators = nullptr;
std::unique_ptr<ATRCFiledata> fd_if = nullptr;
std::unique_ptr<ATRCFiledata> fd_mkdir = nullptr;
std::unique_ptr<ATRCFiledata> fd_rmdir = nullptr;
std::unique_ptr<ATRCFiledata> fd_dir = nullptr;
std::unique_ptr<ATRCFiledata> fd_set = nullptr;
std::unique_ptr<ATRCFiledata> fd_copy = nullptr;
std::unique_ptr<ATRCFiledata> fd_help = nullptr;
std::unique_ptr<ATRCFiledata> fd_move = nullptr;
std::unique_ptr<ATRCFiledata> fd_pause = nullptr;
std::unique_ptr<ATRCFiledata> fd_rename = nullptr;
std::unique_ptr<ATRCFiledata> fd_timeout = nullptr;
std::unique_ptr<ATRCFiledata> fd_string_operators = nullptr;
std::unique_ptr<ATRCFiledata> fd_process_flags = nullptr;
std::unique_ptr<ATRCFiledata> fd_logical_operators = nullptr;
std::unique_ptr<ATRCFiledata> fd_arithmetic_operators = nullptr;
std::unique_ptr<ATRCFiledata> fd_assignment_operators = nullptr;
std::unique_ptr<ATRCFiledata> fd_bitwise_operators = nullptr;


void snw(const std::string& file, std::string& nw, const std::string& path) {
    nw = path + file;
}

std::unique_ptr<ATRCFiledata> reader(const std::string& filename, const std::string& atrc_path) {
    std::string full_path = atrc_path + filename;

    if (!fs::exists(atrc_path)) {
        if (!fs::create_directories(atrc_path)) {
            std::cerr << "Failed to create directory: " << atrc_path << std::endl;
            return nullptr;
        } else {
            std::cout << "Initialized: " << atrc_path << std::endl;
        }
    }
    std::ofstream outfile(full_path, std::ios::app);
    if (!outfile) {
        std::cerr << "Failed to open file: " << full_path << " for appending." << std::endl;
        return nullptr;
    }


    outfile.close();

    std::unique_ptr<ATRCFiledata> temp = Read(full_path, "utf-8");
    if (!temp) {
        std::cerr << "Failed to read file: " << full_path << std::endl;
        return nullptr;
    }

    return temp;
}

void ReadATRC_VALUES(battosh_info *args) {
    std::string home_dir = *args->HOME_PATH;
    std::string atrc_path = home_dir;
#ifdef _WIN32
    if(atrc_path.back() == '\\')
        atrc_path = atrc_path.substr(0, atrc_path.size() - 1);
    atrc_path += "\\battosh\\ATRC\\";
#elif __linux__
    if(atrc_path.back() == '/')
        atrc_path = atrc_path.substr(0, atrc_path.size() - 1);
    atrc_path += "/battosh/ATRC/";
#endif

    std::string now_reading = "";
    fd_battosh = reader("battosh.atrc", atrc_path);
    
    fd_variables = reader("VARIABLES.atrc", atrc_path),
    fd_echo = reader("ECHO.atrc", atrc_path);
    fd_comment = reader("COMMENTS.atrc", atrc_path);
    fd_ver = reader("VER.atrc", atrc_path);
    fd_cls = reader("CLS.atrc", atrc_path);
    fd_call = reader("CALL.atrc", atrc_path);
    fd_type = reader("TYPE.atrc", atrc_path);
    fd_cd = reader("CD.atrc", atrc_path);
    fd_exit = reader("EXIT.atrc", atrc_path);
    fd_relational_operators = reader("RELATIONAL_OPERATORS.atrc", atrc_path);
    fd_if = reader("IF.atrc", atrc_path);
    fd_mkdir = reader("MKDIR.atrc", atrc_path);
    fd_rmdir = reader("RMDIR.atrc", atrc_path);
    fd_dir = reader("DIR.atrc", atrc_path);
    fd_set = reader("SET.atrc", atrc_path);
    fd_copy = reader("COPY.atrc", atrc_path);
    fd_help = reader("HELP.atrc", atrc_path);
    fd_move = reader("MOVE.atrc", atrc_path);
    fd_pause = reader("PAUSE.atrc", atrc_path);
    fd_rename = reader("RENAME.atrc", atrc_path);
    fd_timeout = reader("TIMEOUT.atrc", atrc_path);
    fd_string_operators = reader("STRING_OPERATORS.atrc", atrc_path);
    fd_process_flags = reader("PROCESS_FLAGS.atrc", atrc_path);
    fd_logical_operators = reader("LOGICAL_OPERATORS.atrc", atrc_path);
    fd_arithmetic_operators = reader("ARITHMETIC_OPERATORS.atrc", atrc_path);
    fd_assignment_operators = reader("ASSIGNMENT_OPERATORS.atrc", atrc_path);
    fd_bitwise_operators = reader("BITWISE_OPERATORS.atrc", atrc_path);
}
