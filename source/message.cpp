#include <string>
#include <iostream>
#include <vector>
#include "battosh.hxx"


void message(std::string &msg, int flag, int command, bool error, int line, int column){
    std::string error_msg = "";
    switch (command)
    {
    case HELP_:
        error_msg = 
R"battosh(
Usage:
    battosh {args} [optional]

    args:
        provide path to your batch script

    optional
        -o,     --out                       Set the program to output the shell file with a different filename
        -h,     --help                      See help message
                --version                   See version
                --wsl                       Turn paths to comply with WSL, C:\temp -> /mnt/c/temp.
                --no-linux                  Program does not turn some paths from windows to linux
        -nc,    --no-comments               Program does not save comments
                --disable-atrc-warnings     Disable warning messages from ATRC
                --set-mkdirp                Sets all MKDIR commands to have -p as it is the Windows default
        -qm,    --set-quietmode             CMD flag /Q will be turned to 2> /dev/null
        -ds,    --dir-sort                  When dir is translated to ls, add -l flag to ls (ls -l) 
        -bs,    --bat-shell                 Turn all occurences of .bat to .sh
                --set-home {path}           Give absolute path to where the program will look for config files

    examples:
        battosh file.bat                    -> outputs file.sh
        battosh file.bat -o test.sh         -> outputs test.sh
        battosh file.bat -sw --wsl          -> changes paths to work on wsl, saves whitespaces
)battosh";
        break;
    case VERSION_:
        {
            const char *version = VERSION;
            error_msg = "Version: " + std::string(version);
            break;
        }
    case ATRC_NOT_FOUND:
        error_msg = "ATRC value not found";
        break;
    default:
        break;
    }

    std::cout << "Message: <type:" << command << "-" << flag << " position:" << line << ":" << column << "> " << error_msg << " | " << msg << std::endl;
    if(error){
        exit(command);
    }
}