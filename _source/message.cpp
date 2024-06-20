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
            --wsl                       Turn paths to comply with WSL, C:\temp -> /mnt/c/temp. Cannot be used with --linux. Works only with absolute paths or Windows' standard variables (%USERNAME%, %APPDATA% etc.)
            --linux                     Program tries its best to turn paths from windows to linux, C:\Users\%USERNAME%\Documents -> ~/Documents. Cannot be used with --wsl. Works only with absolute paths or Windows' standard variables (%USERNAME%, %APPDATA% etc.)
    -sw,    --save-whitespace           Program saves the original whitespace and line endings
    -sc,    --save-comments             Program saves the comments
            --set-shell {shell}         Default: /bin/bash. Program will change bash to whatever shell you have provided
            --set-mkdirp                Sets all MKDIR commands to have -p as it is the Windows default
    -qm,    --set-quietmode             CMD flag /Q will be turned to 2> /dev/null
    -ds,    --dir-sort                  When dir is translated to ls, add -l flag to ls (ls -l) 
    -bs,    --bat-shell                 Turn all occurrences of .bat to .sh
            --set-home {path}           Give absolute position for the program to use as home directory instead of the system default. Example: C:\temp\. You will have to create battosh folder there yourself along with all the resource files and its folders
            --disable-atrc-warnings     Disable warning messages from ATRC

examples:
    battosh file.bat                    -> outputs file.sh
    battosh file.bat -o test.sh         -> outputs test.sh
    battosh file.bat -sw --wsl          -> changes paths to work on wsl, saves whitespaces
    battosh file.bat --set-shell zsh    -> turns /bin/bash to /bin/zsh
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