BATch TO SHell

Turn batch scripts to shell scripts

NOTE: Please check the shell scripts before running!

Download:
    See releases
    Windows:
        Standalone executable
        Installer executable
    Linux:
        Standalone executable
        AppImage executable

Usage:
    battosh {args} [optional]

    args:
        provide path to your batch script

    optional
        -o,     --out               Set the program to output the shell file with a different filename
        -h,     --help              See help message
                --version           See version
                --wsl               Turn paths to comply with WSL, C:\temp -> /mnt/c/temp. Can not be used with --linux
                --linux             Program tries its best to turn paths from windows to linux, C:\Users\%USERNAME%\Documents -> ~/Documents. Can not be used with --wsl
        -sw,    --save-whitespace   Program saves the original whitespace and line ends 
        -sc,    --save-comments     Program saves the comments

    Example:
        battosh file.bat                -> outputs file.sh
        battosh file.bat -o test.sh     -> outputs test.sh
        battosh file.bat -sw --wsl      -> changes paths to work on wsl, saves whitespaces


battosh can turn the following commands/statements into bash
ECHO        ->          echo
@REM        ->          #
REM         ->          #
::          ->          #


Known issues:
--save-whitespace does not work properly

Features to be added:



%%%%%%%%%%%%%%%%%%%
    Developing
%%%%%%%%%%%%%%%%%%%

Build and run yourself
    Windows, Visual Studio:
    C++ CMake tools for windows
    C++ v14.xx build tools for (processor)
    MSVC build tools

    Linux:
    Cmake, Ninja and somekind of C++ compiler

    NOTE: See .\<win|linux>\<batch|shell>\globals.<bat|sh>. Enter your paths there or the executable programs if they are found in the PATH

    build project:
    .\<win|linux>\build.<bat|sh>

    run project:
    .\<win|linux>\run.<bat|sh> [args...]

    build and run the project:
    .\build_n_run.<bat|sh> [args...]

    clear build:
    .\<win|linux>\<batch|shell>\del.<bat|sh>
