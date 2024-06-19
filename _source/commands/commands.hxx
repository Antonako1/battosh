#pragma once
#include <string>
// https://tldp.org/LDP/abs/html/dosbatch.html
/*
@echo off
if exist data (
    if not exist "ququ" (
        echo w
    ) else (
        echo q
    )
) else if exist "haha" (
    echo Hi from the other side
) else (
    echo data exists
)


ver
cls
call haha
type test.txt
:: TEST
echo Hi
cd "C:\temp"
exit /B 10

cmake --build . --target test

if not exist data (
    echo data does not exist
) else (
    echo data exists
)
if "A" == "A" echo test
 */
enum batch_commands{
    // FILE COMMANDS
    VER,            // -- (ver) - show version | $SHELL --version      
    ASSOC,          // (assoc) - show or change file associations | chmod
    BREAK,          // (break) - set or clear extended CTRL+C checking | break
    CD,             // -- (cd) - change directory | cd
    CDBACK,         // -- (cd..) - change directory | cd ..
    CHDIR,          // -- (chdir) - change directory | cd
    CLS,            // -- (cls) - clear the screen | clear
    COPY,           // (copy) - copy files | cp
    DEL,            // (del) - delete files | rm
    ERASE,          // (erase) - delete files | rm
    DIR,            // -- (dir) - list directory contents | ls
    DATE,           // (date) - show or set the date |
    ECHO,           // -- (echo) - display message on screen | echo
    EXIT,           // -- (exit) - exit the command interpreter | exit
    MD,             // -- (md) - make directory | mkdir
    MKDIR,          // -- (mkdir) - make directory | mkdir
    MOVE,           // -- (move) - move files | mv
    PATH,           // (path) - display or set a search path for executable files | path
    PAUSE,          // -- (pause) - suspend processing of a batch file and display a message | read -rsp $'Press any key to continue...\n' -n 1 key 
    PROMPT,         // (prompt) - change the command prompt | prompt
    RD,             // -- (rd) - remove directory | rmdir
    RMDIR,          // -- (rmdir) - remove directory | rmdir
    REN,            // -- (ren) - rename files | mv
    RENAME,         // -- (rename) - rename files | mv
    REM,            // -- (rem|@rem) - comment | #
    START,          // (start) - start a program or command | start
    TIME,           // (time) - show or set the system time |
    TYPE,           // -- (type) - display the contents of a text file | cat
    VOL,            // (vol) - display a disk label | vol
    ATTRIB,         // (attrib) - display or change file attributes | chmod
    CHKDSK,         // (chkdsk) - check a disk and display a status report | fsck
    CHOICE,         // (choice) - prompt the user to select one item from a list of single-character choices | choice
    CMD,            // (cmd) - start a new instance of the Windows command interpreter | cmd
    COMP,           // (comp) - compare the contents of two files or sets of files | diff
    CONVERT,        // (convert) - convert a FAT volume to NTFS | convert
    DRIVEQUERY,     // (drivequery) - display current drive letter | drivequery
    EXPAND,         // (expand) - extract files from a compressed file | expand
    FIND,           // (find) - search for a text string in a file | grep
    FORMAT,         // (format) - format a disk for use with Windows | format
    HELP,           // -- (help) - provide Help information for Windows commands | help
    IPCONFIG,       // (ipconfig) - display Windows IP configuration | ipconfig
    LABEL,          // (label) - create, change, or delete the volume label of a disk | label
    MORE,           // (more) - display output, one screen at a time | more
    NET,            // (net) - manage network resources | net
    PING,           // (ping) - test a network connection | ping
    SHUTDOWN,       // (shutdown) - shut down the computer | shutdown
    SORT,           // (sort) - sort input | sort
    SUBST,          // (subst) - associate a path with a drive letter | subst
    SYSTEMINFO,     // (systeminfo) - display system configuration | systeminfo
    TASKKILL,       // (taskkill) - terminate processes by process ID (PID) or image name | taskkill
    TASKLIST,       // (tasklist) - display a list of applications and services | tasklist
    XCOPY,          // (xcopy) - copy files and directory trees | xcopy
    TREE,           // (tree) - display a tree of directories | tree
    FC,             // (fc) - compare two files | fc
    DISKPART,       // (diskpart) - manage disk partitions | diskpart
    TITLE,          // (title) - set the window title for a CMD.EXE session | title
    SET,            // (set) - display, set, or remove CMD environment variables | set
    
    // CONTROL COMMANDS
    IF,             // -- (if) - perform conditional processing in batch programs | if
    ELSE,           // -- (else) - perform conditional processing in batch programs | else
    ELSEIF,         // -- (else if) - perform conditional processing in batch programs | elseif
    FOR,            // (for) - conditionally perform a command several times | for
    GOTO,           // (goto) - direct a batch program to jump to a labelled line | goto
    GOTODEFINITION, // (:) - direct a batch program to jump to a labelled line | :
    CALL,           // -- (call) - call one batch program from another | call
    SHIFT,          // (shift) - change the position of replaceable parameters in a batch program | shift
    SETLOCAL,       // (setlocal) - begin localisation of environment changes in a batch file | setlocal
    ENDLOCAL,       // (endlocal) - end localisation of environment changes in a batch file | endlocal

    // UTILITY COMMANDS
    FINDSTR,        // (findstr) - search for strings in files | findstr
    TIMEOUT,        // -- (timeout) - pause the command processor | timeout
    SCHTASKS,       // (schtasks) - schedule a command to run at a specific time | schtasks
    WMIC,           // (wmic) - Windows Management Instrumentation Command | wmic
    SC,             // (sc) - Service Control | sc
    REG,            // (reg) - Read, Set or Delete registry keys and values | reg
    POWERCFG,       // (powercfg) - Configure power settings | powercfg
    BITSADMIN,      // (bitsadmin) - Background Intelligent Transfer Service | bitsadmin
    CIPHER,         // (cipher) - Encrypt or Decrypt files/folders | cipher
    COMPACT,        // (compact) - Compress files or folders | compact
    DISKCOMP,       // (diskcomp) - Compare the contents of two floppy disks | diskcomp
    DISKCOPY,       // (diskcopy) - Copy the contents of one floppy disk to another | diskcopy
    DRIVERQUERY,    // (driverquery) - Display installed device drivers | driverquery
    FSUTIL,         // (fsutil) - File and Volume utilities | fsutil
    GPRESULT,       // (gpresult) - Group Policy Results | gpresult
    LOGMAN,         // (logman) - Manage Performance Monitor | logman

    // Flags
    FLAG,           // -- /?, /S, /Q etc.

    // Variable
    VAR,            // %var%
    SETX,           // (setx) - Set environment variables | setx
    
    // Unknown
    UNKNOWN,

    // Separator
    LPAREN,         // -- (
    RPAREN,         // -- )


    ENDLINE,        

    COMMENT,        // -- #
    ECHOOFF,        // -- @echo off/on

    NULL__TOKEN,

    // Comparison Operators
    EQU,            // -- -eq
    NEQ,            // -- -ne
    LSS,            // -- -lt
    LEQ,            // -- -le
    GTR,            // -- -gt
    GEQ,            // -- -ge

    // logical Operators
    AND,            // -- &&
    OR,             // -- ||
    NOT,            // -- !
    SHL,            // -- << NOTE ?
    SHR,            // -- >> NOTE ?

    // Assignment Operators
    ADD_ASSIGN,     // +=
    SUB_ASSIGN,     // -=
    MUL_ASSIGN,     // *=
    DIV_ASSIGN,     // /=
    MOD_ASSIGN,     // %=
    
    // Bitwise Operators
    AND_BIT,        // -- -a
    OR_BIT,         // -- -o
    XOR,            // -- ^ // TODO: XOR operator

    // TODO STRING OPERATORS: =, !=, -z, -n, str https://www.tutorialspoint.com/unix/unix-basic-operators.htm
    
    // Arithmetic Operators
    ADD,            // +
    SUB,            // -
    MUL,            // *
    DIV,            // /
    MOD,            // %

    EXIST,          // -- (exist) - check if file exists | 

};


struct ECHO_FLAG{
    std::string LINUX_GET_GELP_UPDATED_PATH = "/bin/echo";
    std::string LINUX_GET_HELP = "--help";
    std::string LINUX_GET_HELP_EXPECT_VALUE = "NONE";
    std::string GET_HELP = "/?";
    std::string GET_HELP_EXPECT_VALUE = "NONE";
};

struct EXIT_FLAG{
    std::string LINUX_EXIT_CURRENT_BATCH = "";
    std::string LINUX_EXIT_CURRENT_BATCH_EXPECT_VALUE = "INT";
    std::string EXIT_CURRENT_BATCH = "/B";
    std::string EXIT_CURRENT_BATCH_EXPECT_VALUE = "INT";      
    
    std::string LINUX_GET_HELP = "--help";
    std::string GET_HELP = "/?";
    std::string GET_HELP_EXPECT_VALUE = "NONE";
};

struct MKDIR_FLAG{
    std::string LINUX_GET_HELP = "--help";
    std::string GET_HELP = "/?";
    std::string GET_HELP_EXPECT_VALUE = "NONE";
};

struct RENAME_FLAG{
    std::string LINUX_GET_HELP = "--help";
    std::string GET_HELP = "/?";
    std::string GET_HELP_EXPECT_VALUE = "NONE";
};

struct RMDIR_FLAG{
    std::string LINUX_GET_HELP = "--help";
    std::string GET_HELP = "/?";
    std::string GET_HELP_EXPECT_VALUE = "NONE";

    std::string LINUX_UPDATED_COMMAND = "rm";
    std::string LINUX_REMOVE_DIR_TREE = "-rf";
    std::string REMOVE_DIR_TREE = "/S";
    std::string REMOVE_DIR_TREE_EXPECT_VALUE = "NONE";
    
    // std::string LINUX_QUIET_MODE = "2> /dev/null";
    // std::string LINUX_QUIET_MODE = "";
    std::string QUIET_MODE = "/Q";

};

struct IF_FLAG{
    std::string LINUX_GET_HELP = "--help";
    std::string GET_HELP = "/?";
    std::string GET_HELP_EXPECT_VALUE = "NONE";

    // TODO: do /I once variable is implemented
    std::string LINUX_IGNORE_CASE = "\"$var,,}\"";
    std::string IGNORE_CASE = "/I";
    std::string IGNORE_CASE_EXPECT_VALUE = "NONE";
};

struct TIMEOUT_FLAG{
    std::string LINUX_GET_HELP = "--help";
    std::string GET_HELP = "/?";
    std::string GET_HELP_EXPECT_VALUE = "NONE";

    std::string TIMEOUT = "/T";
    std::string TIMEOUT_EXPECT_VALUE = "INT";

    std::string NO_INTERRUPT = "/NOBREAK"; // no linux equivalent
};

struct MOVE_FLAG {
    std::string LINUX_GET_HELP = "--help";
    std::string GET_HELP = "/?";
    std::string GET_HELP_EXPECT_VALUE = "NONE";

    std::string LINUX_FORCE_MOVE = "--force";
    std::string FORCE_MOVE = "/Y";
    std::string FORCE_MOVE_EXPECT_VALUE = "NONE";

    std::string LINUX_PROMPT = "--interactive";
    std::string PROMPT = "/-Y";
};

struct HELP_FLAG {
    std::string LINUX_GET_HELP = "--help";
    std::string HELP = "/?";
    std::string HELP_EXPECT_VALUE = "NONE";
};

struct PAUSE_FLAG {
    // not my own code, copied from https://stackoverflow.com/a/17778773/22872825
    std::string LINUX_PAUSE = "read -rsp $'Press any key to continue...\\n' -n 1 key ";
};

struct DIR_FLAG {
    std::string LINUX_GET_HELP = "--help";
    std::string GET_HELP = "/?";
    std::string GET_HELP_EXPECT_VALUE = "NONE";

    std::string LINUX_ATTRIBUTES_NO_ATTRIB  = "-a "; // /A flag shows everything, this is the closest to it
    std::string LINUX_ATTRIBUTES_DIRS           = "-d */";      // /A:D  
                                                // PATH HERE
    std::string LINUX_ATTRIBUTES_DIRS_ENDING    = "*/";      // /A:D  

    std::string LINUX_ATTRIBUTES_READ_ONLY      = "find "; // /A:R
                                                // PATH HERE
    std::string LINUX_ATTRIBUTES_RO_ENDING      = " -maxdepth 1 -type f ! -writable"; // /A:R
    
    std::string LINUX_ATTRIBUTES_HIDDEN         = "-d "; // /A:H
                                                // PATH HERE
    std::string LINUX_ATTRIBUTES_HIDDEN_ENDING  = ".* "; // /A:H

    std::string LINUX_ATTRIBUTES_ARCHIVE        = ""; // /A:A, no linux equivalent

    std::string LINUX_ATTRIBUTES_SYSTEM         = "find"; // /A:S
                                                // PATH HERE
    std::string LINUX_ATTRIBUTES_SYSTEM_ENDING  = "-maxdepth 1 -type f \\( -perm /u=s -o -perm /g=s -o -perm /o=s \\)"; // /A:S

    std::string LINUX_ATTRIBUTES_NON_INDEXED    = ""; // /A:I, no linux equivalent
    std::string LINUX_ATTRIBUTES_REPARSE_POINT  = ""; // /A:L, no linux equivalent
    std::string LINUX_ATTRIBUTES_OFFLINE        = ""; // /A:O, no linux equivalent
    std::string LINUX_ATTRIBUTES_PREFIX_NOT     = "! "; // /A:-

    std::string ATTRIBUTES                  = "/A";
    std::string ATTRIBUTES_DIRS                 = ":D";
    std::string ATTRIBUTES_READ_ONLY            = ":R";
    std::string ATTRIBUTES_HIDDEN               = ":H";
    std::string ATTRIBUTES_ARCHIVE              = ":A";
    std::string ATTRIBUTES_SYSTEM               = ":S";
    std::string ATTRIBUTES_NON_INDEXED          = ":I";
    std::string ATTRIBUTES_REPARSE_POINT        = ":L";
    std::string ATTRIBUTES_OFFLINE              = ":O";
    std::string ATTRIBUTES_PREFIX_NOT           = ":-"; // example: dir /A:d-s -> show all directories exluding system directories
    std::string ATTRIBUTES_EXPECT_VALUE = "STRING";
};