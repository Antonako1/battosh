# BATch TO SHell

### Turn batch scripts to shell scripts on Windows and Linux

NOTE! Please check the shell scripts before running them! Everything cannot be changed from batch to shell the way the user probably intended.


The program uses ATRC resource file library. Documentation on how to work with it is written into  ```.\ATRC\README.txt ```

For most of the commands, the defaults are there for a reason but you can modify them.
 
Resource files will be downloaded to:

Linux: ```~/.config/battosh/ATRC```

Windows: ```C:\Users\%USERNAME%\battosh\ATRC```

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
                    --wsl                       Turn paths to comply with WSL, C:\temp -> /mnt/c/temp.
                    --no-linux                  Program does not turn some paths from windows to linux
            -nc,    --no-comments               Program does not save comments
                    --disable-atrc-warnings     Disable warning messages from ATRC
                    --set-shell {shell}         Default: /bin/bash. Program will change bash to whatever shell you have provided
                    --set-mkdirp                Sets all MKDIR commands to have -p as it is the Windows default
            -qm,    --set-quietmode             CMD flag /Q will be turned to 2> /dev/null
            -ds,    --dir-sort                  When dir is translated to ls, add -l flag to ls (ls -l) 
            -bs,    --bat-shell                 Turn all occurences of .bat to .sh
                    --set-home {path}           Give absolute path to where the program will look for config files

        examples:
            battosh file.bat                    -> outputs file.sh
            battosh file.bat -o test.sh         -> outputs test.sh
            battosh file.bat -sw --wsl          -> changes paths to work on wsl, saves whitespaces
            battosh file.bat --set-shell zsh    -> turns /bin/bash to /bin/zsh

see file processing flags to inject and modify code during compile `ATRC\PROCESS_FLAGS.atrc`

battosh can turn the following commands/statements with their flags into bash

    Variables               =>              See ATRC\VARIABLES.atrc
    ECHO                    =>              See ATRC\ECHO.atrc
    @ECHO (on/off)          =>              See ATRC\ECHO.atrc
    (@)REM, ::              =>              See ATRC\COMMENTS.atrc
    VER                     =>              See ATRC\VER.atrc
    CLS                     =>              See ATRC\CLS.atrc
    CALL                    =>              See ATRC\CALL.atrc
    TYPE                    =>              See ATRC\TYPE.atrc
    CD, CHDIR, CD..         =>              See ATRC\CD.atrc
    EXIT                    =>              See ATRC\EXIT.atrc
    Relational operators    =>              See ATRC\RELATIONAL_OPERATORS.atrc
    Logical operators       =>              See 
    Assignment operators    =>              See
    Bitwise operators       =>              See
    Arithmetic operators    =>              See
    String operators        =>              See
    IF, ELSE(ELSE IF)       =>              See ATRC\IF.atrc
    MKDIR, MD               =>              See ATRC\MKDIR.atrc
    RMDIR, RD               =>              See ATRC\RMDIR.atrc
    REN, RENAME             =>              See
    TIMEOUT                 =>              See
    MOVE                    =>              See
    HELP                    =>              See
    PAUSE                   =>              See
    DIR                     =>              See
    SET                     =>              See ATRC\SET.atrc

### Known issues

- --save-whitespace and comment ignoring leaves empty rows there, where the comments were
- If statement intending is broken sometimes
- If comment is trailing a statement, it will become part of it

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

In .\release_building, run win.bat and linux.sh to build all the release binaries
