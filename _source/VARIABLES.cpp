#include <iostream>
#include <string>
#include <vector>

#include "VARIABLES.hxx"
#include "battosh.hxx"
#include "./commands/commands.hxx"

std::string VARIABLES[] = {
    "%ALLUSERSPROFILE%",                  std::to_string(ALLUSERSPROFILE),
    "%APPDATA%",                          std::to_string(APPDATA),
    "%CommonProgramFiles%",               std::to_string(CommonProgramFiles),
    "%CommonProgramFiles(x86)%",            std::to_string(CommonProgramFilesx86),
    "%CommonProgramW6432%",               std::to_string(CommonProgramW6432),
    "%COMPUTERNAME%",                     std::to_string(COMPUTERNAME),
    "%ComSpec%",                          std::to_string(ComSpec),
    "%DriverData%",                       std::to_string(DriverData),
    "%HOMEDRIVE%",                        std::to_string(HOMEDRIVE),
    "%HOMEPATH%",                         std::to_string(HOMEPATH),
    "%LOCALAPPDATA%",                     std::to_string(LOCALAPPDATA),
    "%LOGONSERVER%",                      std::to_string(LOGONSERVER),
    "%NUMBER_OF_PROCESSORS%",             std::to_string(NUMBER_OF_PROCESSORS),
    "%OneDrive%",                         std::to_string(OneDrive),
    "%OneDriveConsumer%",                 std::to_string(OneDriveConsumer),
    "%OS%",                               std::to_string(OS),
    "%Path%",                             std::to_string(Path),
    "%PATHEXT%",                          std::to_string(PATHEXT),
    "%POWERSHELL_DISTRIBUTION_CHANNEL%",  std::to_string(POWERSHELL_DISTRIBUTION_CHANNEL),
    "%PROCESSOR_ARCHITECTURE%",           std::to_string(PROCESSOR_ARCHITECTURE),
    "%PROCESSOR_IDENTIFIER%",             std::to_string(PROCESSOR_IDENTIFIER),
    "%PROCESSOR_LEVEL%",                  std::to_string(PROCESSOR_LEVEL),
    "%PROCESSOR_REVISION%",               std::to_string(PROCESSOR_REVISION),
    "%ProgramData%",                      std::to_string(ProgramData),
    "%ProgramFiles%",                     std::to_string(ProgramFiles),
    "%ProgramFiles(x86)%",                  std::to_string(ProgramFilesx86),
    "%ProgramW6432%",                     std::to_string(ProgramW6432),
    "%PROMPT%",                           std::to_string(PROMPT_),
    "%PSModulePath%",                     std::to_string(PSModulePath),
    "%PUBLIC%",                           std::to_string(PUBLIC),
    "%SESSIONNAME%",                      std::to_string(SESSIONNAME),
    "%SystemDrive%",                      std::to_string(SystemDrive),
    "%SystemRoot%",                       std::to_string(SystemRoot),
    "%TEMP%",                             std::to_string(TEMP),
    "%TMP%",                              std::to_string(TMP),
    "%USERDOMAIN%",                       std::to_string(USERDOMAIN),
    "%USERDOMAIN_ROAMINGPROFILE%",        std::to_string(USERDOMAIN_ROAMINGPROFILE),
    "%USERNAME%",                         std::to_string(USERNAME),
    "%USERPROFILE%",                      std::to_string(USERPROFILE),
    "%VBOX_MSI_INSTALL_PATH%",            std::to_string(VBOX_MSI_INSTALL_PATH),
    "%windir%",                           std::to_string(windir),
    "%WSLENV%",                           std::to_string(WSLENV),
    "%WT_PROFILE_ID%",                    std::to_string(WT_PROFILE_ID),
    "%WT_SESSION%",                       std::to_string(WT_SESSION),
    "%ZES_ENABLE_SYSMAN%",                std::to_string(ZES_ENABLE_SYSMAN),
};

char look_ahead(size_t index, std::string &line){
    if(index >= line.size()){
        return '\0';
    }
    return line[index];
}

void variablify(std::string &input, battosh_info *args){
    size_t index = 0;
    std::string buffer = "";
	bool buffer_used = false;
    for(index = 0; index < input.size(); index++){
        char ahead = look_ahead(index, input);
        
    }
}
