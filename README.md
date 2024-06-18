# BATch TO SHell

### Turn batch scripts to shell scripts on Windows and Linux

NOTE: Please check the shell scripts before running them! Everything cannot be changed from batch to shell the way the user probably intended.

## Download

See [releases](https://github.com/Antonako1/battosh/releases)

Windows:

- Standalone executable
- Installer executable

Linux:

- Standalone executable
- AppImage executable

## Usage

        battosh {args} [optional]

        args:
            provide path to your batch script

        optional
            -o,     --out                       Set the program to output the shell file with a different filename
            -h,     --help                      See help message
                    --version                   See version
                    --wsl                       Turn paths to comply with WSL, C:\temp -> /mnt/c/temp. Can not be used with --linux
                    --linux                     Program tries its best to turn paths from windows to linux, C:\Users\%USERNAME%\Documents -> ~/Documents. Can not be used with --wsl
            -sw,    --save-whitespace           Program saves the original whitespace and line ends 
            -sc,    --save-comments             Program saves the comments
                    --set-shell {shell}         Default: /bin/bash. Program will change bash to whatever shell you have provided
                    --set-mkdirp                Sets all MKDIR commands to have -p as it is the Windows default
        examples:
            battosh file.bat                    -> outputs file.sh
            battosh file.bat -o test.sh         -> outputs test.sh
            battosh file.bat -sw --wsl          -> changes paths to work on wsl, saves whitespaces
            battosh file.bat --set-shell zsh    -> turns /bin/bash to /bin/zsh

battosh can turn the following commands/statements into bash

    usermade program
    cmake --build .     ->              usermade program
                                        cmake --build .
    ECHO, /?            ->              echo, /bin/echo --help
    @REM                ->              #
    REM                 ->              #
    ::                  ->              #
    ver                 ->              $SHELL --version
    cls                 ->              clear
    call                ->              call
    type                ->              cat
    cd                  ->              cd
    exit, /?, /B        ->              exit, --help, exit [n]
    if else, else if
    comparisons,
    exist
    /I                  ->              if else, elif
                                        comparisons
                                        -e
                                        only works for variables... ("${var1,,}" = "${var2,,}")
    mkdir, /?           ->              mkdir, --help

### Known issues

- --save-whitespace and comment ignoring leaves empty rows there, where the comments were
- Paths like: C:\temp turn to C : \temp. please do "C:\temp" in the meantime



## Developing

### Build and run yourself

    Windows, Visual Studio:
        C++ CMake tools for windows
        C++ v14.xx build tools for (processor)
        MSVC build tools

    Windows, Cygwin, MSYS:
        I don't know...
        Cmake, Ninja and somekind of C++ compiler should work?

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

## Releasing

In .\release_building, run win.bat and then linux.sh to build all the release binaries