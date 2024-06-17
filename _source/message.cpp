#include <string>
#include <iostream>
#include <vector>
#include "battosh.hxx"

void message(std::string &msg, int flag, int command, bool error, int line, int column){
    std::string error_msg = "";
    switch (command)
    {
    case HELP_:
        error_msg = "Usage: battosh {args} [optional]";
        break;
    case VERSION_:
        error_msg = "battosh version " + std::to_string(MAJOR_VERSION) + "." + std::to_string(MINOR_VERSION) + "." + std::to_string(PATCH_VERSION);
        break;
    default:
        break;
    }

    std::cout << "Error: <type:" << command << "-" << flag << " position:" << line << ":" << column << "> " << error_msg << " | " << msg << std::endl;
    if(error){
        exit(command);
    }
}