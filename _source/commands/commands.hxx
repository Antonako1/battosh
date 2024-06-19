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
    ASSOC,          // (assoc) - show or change file associations | chmod?
    CD,             // -- (cd) - change directory | cd
    CHDIR,          // -- (chdir) - change directory | cd
    CLS,            // -- (cls) - clear the screen | clear
    COPY,           // (copy) - copy files | cp
    DEL,            // (del) - delete files | rm
    DIR,            // (dir) - list directory contents | ls
    DATE,           // (date) - show or set the date |
    ECHO,           // -- (echo) - display message on screen | echo
    EXIT,           // -- (exit) - exit the command interpreter | exit
    MD,             // -- (md) - make directory | mkdir
    MKDIR,          // -- (mkdir) - make directory | mkdir
    MOVE,           // -- (move) - move files | mv
    PATH,           // (path) - display or set a search path for executable files | path
    PAUSE,          // (pause) - suspend processing of a batch file and display a message | sleep
    PROMPT,         // (prompt) - change the command prompt | prompt
    RD,             // -- (rd) - remove directory | rmdir
    RMDIR,          // -- (rmdir) - remove directory | rmdir
    REN,            // -- (ren) - rename files | mv
    RENAME,         // -- (rename) - rename files | mv
    REM,            // -- (rem|@rem) - comment | #
    START,          // (start) - start a program or command | start
    TIME,           // (time) - show or set the system time |
    TYPE,           // (type) - display the contents of a text file | cat
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
    HELP,           // (help) - provide Help information for Windows commands | help
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
    FLAG,           // /?, /S, /Q etc.

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

    // Comparison 
    EQU,            // -- ==
    NEQ,            // -- !=
    LSS,            // -- <
    LEQ,            // -- <=
    GTR,            // -- >
    GEQ,            // -- >=

    // Operators
    AND,            // -- &&
    OR,             // -- ||
    NOT,            // -- !
    XOR,            // -- ^
    SHL,            // -- <<
    SHR,            // -- >>

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