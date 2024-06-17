#pragma once
#include <string>
enum batch_commands{
    // FILE COMMANDS
    ___,
    VER,            // (ver) - show version |
    ASSOC,          // (assoc) - show or change file associations |
    CD,             // (cd) - change directory | cd
    CLS,            // (cls) - clear the screen | clear
    COPY,           // (copy) - copy files | cp
    DEL,            // (del) - delete files | rm
    DIR,            // (dir) - list directory contents | ls
    DATE,           // (date) - show or set the date |
    ECHO,           // (echo) - display message on screen | echo
    EXIT,           // (exit) - exit the command interpreter | exit
    MD,             // (md) - make directory | mkdir
    MKDIR,          // (mkdir) - make directory | mkdir
    MOVE,           // (move) - move files | mv
    PATH,           // (path) - display or set a search path for executable files | path
    PAUSE,          // (pause) - suspend processing of a batch file and display a message | pause
    PROMPT,         // (prompt) - change the command prompt | prompt
    RD,             // (rd) - remove directory | rmdir
    RMDIR,          // (rmdir) - remove directory | rmdir
    REN,            // (ren) - rename files | mv
    REM,            // (rem|@rem) - comment | #
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
    IF,             // (if) - perform conditional processing in batch programs | if
    ELSE,           // (else) - perform conditional processing in batch programs | else
    FOR,            // (for) - conditionally perform a command several times | for
    GOTO,           // (goto) - direct a batch program to jump to a labelled line | goto
    CALL,           // (call) - call one batch program from another | call
    SHIFT,          // (shift) - change the position of replaceable parameters in a batch program | shift
    SETLOCAL,       // (setlocal) - begin localisation of environment changes in a batch file | setlocal
    ENDLOCAL,       // (endlocal) - end localisation of environment changes in a batch file | endlocal

    // UTILITY COMMANDS
    FINDSTR,        // (findstr) - search for strings in files | findstr
    TIMEOUT,        // (timeout) - pause the command processor | timeout
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
    LPAREN,         // (
    RPAREN,         // )


    ENDLINE,        

    COMMENT,        // #
    ECHOOFF,        // @echo off/on

    NULL__TOKEN
};

struct ECHO_FLAG{
    std::string ECHO_COMMAND = "ECHO";
    std::string ECHO_EXPECT_VALUE = "?ANY";
    
    std::string ECHO_GET_HELP = "/?";
    std::string ECHO_GET_HELP_EXPECT_VALUE = "NONE";
};

struct EXIT_FLAG{
    std::string EXIT_COMMAND = "ECHO";
    std::string EXIT_EXPECT_VALUE = "?INT";

    std::string EXIT_CURRENT_BATCH = "/B";
    std::string EXIT_CURRENT_BATCH_EXPECT_VALUE = "INT";      
    
    std::string EXIT_GET_HELP = "/?";
    std::string EXIT_GET_HELP_EXPECT_VALUE = "NONE";
};



