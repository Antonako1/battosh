#include "battosh.hxx"
#include "ATRC_VALUES.hxx"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <ctime>

namespace fs = std::filesystem;


std::string output_log = "";
std::string filename;



void write_to_output_log(std::string log){
    output_log += log + "\n";
}

void save_output_log(){
    std::ofstream outfile(filename, std::ios::app);
    outfile << "Log file " + filename + " created.\n";
    if (!outfile) {
        std::cerr << "Failed to open file: " << filename << " for appending." << std::endl;
        return;
    }
    outfile << output_log;
    outfile << "Closing log file.\n";
    outfile.close();
}

void start_output_log(battosh_info *args){
    std::string path = *args->HOME_PATH + 
#ifdef _WIN32
    "\\battosh\\logs\\";
#elif __linux__
    "/battosh/logs/";
#endif
    if (!fs::exists(path)) {
        if (!fs::create_directories(path)) {
            std::cerr << "Failed to create directory: " << path << std::endl;
            return;
        } else {
            std::cout << "Initialized: " << path << std::endl;
        }
    }

    
    time_t now = time(0);
    struct tm tm;
    localtime_s(&tm, &now);
    char str[26];
    asctime_s(str, sizeof str, &tm); 

    filename = path + "battosh_log-";
    filename += std::to_string(tm.tm_year + 1900) + "";
    filename += std::to_string(tm.tm_mon  + 1)    + "";
    filename += std::to_string(tm.tm_mday)        + "";
    filename += std::to_string(tm.tm_hour)        + "";
    filename += std::to_string(tm.tm_min)         + "";
    filename += std::to_string(tm.tm_sec);
    filename += ".txt";
    std::cout << "Log file created at: " << filename << std::endl;
}