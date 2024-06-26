#ifndef VARIABLES_H
#define VARIABLES_H

#include <string>
#include "battosh.hxx"

enum Variables {
    ALLUSERSPROFILE,                    // C:\ProgramData                           | ~/.config
    APPDATA,                            // C:\Users\{user}\AppData\Roaming\{appname}| ~/.{appname} || ~/.config/{appname}
    CommonProgramFiles,                 // C:\Program Files\Common Files            | /usr/share
    CommonProgramFilesx86,              // C:\Program Files (x86)\Common Files      | /usr/share
    CommonProgramW6432,                 // C:\Program Files\Common                  | /usr/share
    COMPUTERNAME,                       //
    ComSpec,                            // C:\Windows\System32\cmd.exe              | $SHELL
    DriverData,                         // C:\Windows\System32\Drivers\dir          | /lib/modules
    HOMEDRIVE,                          // C:                                       | /
    HOMEPATH,                           // \Users\{user}                            | /home/{user}
    LOCALAPPDATA,                       // C:\Users\{user}\AppData\Local            | ~/.local
    LOGONSERVER,                        // \\{domain}                               | $HOSTNAME              
    NUMBER_OF_PROCESSORS,               //
    OneDrive,                           // C:\Users\{user}\OneDrive                 |
    OneDriveConsumer,                   // C:\Users\{user}\OneDrive                 |
    OS,                                 //
    Path,                               // 
    PATHEXT,                            //
    POWERSHELL_DISTRIBUTION_CHANNEL,    //
    PROCESSOR_ARCHITECTURE,             //    
    PROCESSOR_IDENTIFIER,               //
    PROCESSOR_LEVEL,                    //
    PROCESSOR_REVISION,                 //
    ProgramData,                        // C:\ProgramData                           | ~/.config
    ProgramFiles,                       // C:\Program Files                         | /usr
    ProgramFilesx86,                    // C:\Program Files (x86)                   | /usr
    ProgramW6432,                       // C:\Program Files                         | /usr
    PROMPT_,                            //  
    PSModulePath,                       //
    PUBLIC,                             // C:\Users\Public                          | /usr/share
    SESSIONNAME,                        //
    SystemDrive,                        // C:                                       | /            
    SystemRoot,                         // C:\Windows                               | /usr
    TEMP,                               // C:\Users\{user}\AppData\Local\Temp       | /tmp
    TMP,                                // C:\Users\{user}\AppData\Local\Temp       | /tmp
    USERDOMAIN,                         //
    USERDOMAIN_ROAMINGPROFILE,          //
    USERNAME,                           // {user}                                   | $USER
    USERPROFILE,                        // C:\Users\{user}                          | /home/{user}
    VBOX_MSI_INSTALL_PATH,              //
    windir,                             // C:\Windows                               | /usr
    WSLENV,                             //
    WT_PROFILE_ID,                      //
    WT_SESSION,                         //
    ZES_ENABLE_SYSMAN,                  //
    TIME__,
    RANDOM,
    ERRORLEVEL,
    DATE__,
    CMDCMDLINE,
    CMDEXTVERSION,
    CD__,
};

void variablify(std::string &input, battosh_info *args);

#endif // VARIABLES_H
