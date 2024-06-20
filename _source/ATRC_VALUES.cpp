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

std::unique_ptr<ATRCFiledata> fd_echo = nullptr;
std::unique_ptr<ATRCFiledata> fd_comment = nullptr;
std::unique_ptr<ATRCFiledata> fd_ver = nullptr;
std::unique_ptr<ATRCFiledata> fd_cls = nullptr;
std::unique_ptr<ATRCFiledata> fd_call = nullptr;
std::unique_ptr<ATRCFiledata> fd_type = nullptr;
std::unique_ptr<ATRCFiledata> fd_cd = nullptr;
std::unique_ptr<ATRCFiledata> fd_exit = nullptr;
std::unique_ptr<ATRCFiledata> fd_arithmetic_operators = nullptr;



void snw(const std::string& file, std::string& nw, const std::string& path) {
    nw = path + file;
}

std::unique_ptr<ATRCFiledata> reader(const std::string& filename, const std::string& now_reading, const std::string& atrc_path) {
    std::string full_path = atrc_path + filename;

    // Create directories if they do not exist
    if (!fs::exists(atrc_path)) {
        if (!fs::create_directories(atrc_path)) {
            std::cerr << "Failed to create directory: " << atrc_path << std::endl;
            return nullptr;
        } else {
            std::cout << "Initialized: " << atrc_path << std::endl;
        }
    }
    // Open the file for appending and reading (create if not exists)
    std::ofstream outfile(full_path, std::ios::app);
    if (!outfile) {
        std::cerr << "Failed to open file: " << full_path << " for appending." << std::endl;
        return nullptr;
    }

    // Check if file is empty
    // if (outfile.tellp() == 0) {
    //     // File is empty, write initial content
    //     outfile << "[temp]\ntemp=temp\n";
    // }

    outfile.close();

    // Read the file
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

    // cleanup();

    fd_echo = reader("ECHO.atrc", now_reading, atrc_path);
    fd_comment = reader("COMMENTS.atrc", now_reading, atrc_path);
    fd_ver = reader("VER.atrc", now_reading, atrc_path);
    fd_cls = reader("CLS.atrc", now_reading, atrc_path);
    fd_call = reader("CALL.atrc", now_reading, atrc_path);
    fd_type = reader("TYPE.atrc", now_reading, atrc_path);
    fd_cd = reader("CD.atrc", now_reading, atrc_path);
    fd_exit = reader("EXIT.atrc", now_reading, atrc_path);
    fd_arithmetic_operators = reader("ARITHMETIC_OPERATORS.atrc", now_reading, atrc_path);
}

// void cleanup() {
//     fd_echo.reset();
//     fd_comment.reset();
// }
