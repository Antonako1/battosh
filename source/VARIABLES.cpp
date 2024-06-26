#include <iostream>
#include <string>
#include <vector>

#include "VARIABLES.hxx"
#include "ATRC_VALUES.hxx"
#include "battosh.hxx"
#include "./commands/commands.hxx"

std::string VARIABLES[] = {
    "%ALLUSERSPROFILE%",                  std::to_string(ALLUSERSPROFILE),
    "%APPDATA%",                          std::to_string(APPDATA),
    "%CommonProgramFiles%",               std::to_string(CommonProgramFiles),
    "%CommonProgramFiles(x86)%",          std::to_string(CommonProgramFilesx86),
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
    "%ProgramFiles(x86)%",                std::to_string(ProgramFilesx86),
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
    "%windir%",                           std::to_string(windir),
	"%TIME%",							  std::to_string(TIME__),
	"%RANDOM%",					    	  std::to_string(RANDOM),
	"%ERRORLEVEL%",				     	  std::to_string(ERRORLEVEL),
	"%DATE%",					    	  std::to_string(DATE__),
	"%CMDCMDLINE%",				    	  std::to_string(CMDCMDLINE),
	"%CMDEXTVERSION%",			    	  std::to_string(CMDEXTVERSION),
	"%CD%",						    	  std::to_string(CD__),
};
// void clear_previous(std::string &buffer, int match){
// 	//buffer = buffer.substr(, (VARIABLES[match-1].size() - 1));
// 	buffer = "";
// }
std::tuple<int, int> check_for_full_var_matches(std::string &buffer){
	for(int i = 0; i < sizeof(VARIABLES)/sizeof(VARIABLES[0]); i+=2){
        if(buffer == VARIABLES[i]){
			std::cout << buffer << " : " << VARIABLES[i] << " : " << i << " : " << std::stoi(VARIABLES[i+1]) << std::endl;
            return {i, std::stoi(VARIABLES[i+1])};
        }
    }

    return {-1, -1};
}

char look_ahead(size_t index, std::string &line){
    if(index >= line.size()){
        return '\0';
    }
    return line[index];
}

void variablify(std::string &input, battosh_info *args){
    size_t index = 0;
	std::string revised_input = "";
    std::string buffer = "";
	bool buffer_used = false;
    for(index = 0; index < input.size(); index++){
        char ahead = look_ahead(index, input);
		if(ahead != '%') {
       		revised_input += ahead;
			continue;
		}
		buffer += ahead;
		index++;
		ahead = look_ahead(index, input);
		if(ahead == '%'){ // look for %%x
		    buffer += ahead;
			index++;
			ahead = look_ahead(index, input);
			buffer += ahead;
			//buffer contains %%x
			buffer_used = true;
		}
		
		if(!buffer_used && ahead == '~'){
			while(!std::isdigit(ahead)){
				ahead = look_ahead(index, input);
				buffer += ahead;
				index++;
			}
			ahead = look_ahead(index, input);
			// buffer contains %~(d|p|n|x)<single_digit>
			buffer_used = true;

			// after processing, add the ahead
			buffer += ahead;
		}
		// TODO check for percent colon 

		if(!buffer_used){
			bool end_found = false;
			if(!std::isdigit(ahead)) {
				while(index < input.size() - 1){
					ahead = look_ahead(index, input);
					buffer += ahead;

					// Bad fix
					if(ahead == '"') {
						buffer += ahead;
						break;
					};
					if(ahead == '%'){
						end_found = true;
						break;
					}
					index++;
				}
			} else {
				buffer += ahead;
			}
			int array_index, match = 0;
			if(!end_found || args->no_linux){
				array_index, match = -1;
			} 
			
			//buffer contains %x% or %<digit>
			else {
				const std::tuple results_ = check_for_full_var_matches(buffer);
				array_index = std::get<0>(results_);
				match = std::get<1>(results_);
			}

			std::string cts1 = "";
			std::string df_input = "";

			switch(match){
				case ALLUSERSPROFILE:
				case APPDATA:
					df_input = "~/.config";
					break;
				case CommonProgramFiles:
				case CommonProgramFilesx86:
				case CommonProgramW6432:{
					df_input = "/usr";
					break;						
				}
				case COMPUTERNAME:
					 df_input = "$NAME";
                     break;
				case ComSpec:
                    df_input = "$SHELL";
					break;
				case DriverData:
                   df_input = "/lib/modules";
					break;
				case HOMEDRIVE:
                   df_input = "c";
					break;
				case HOMEPATH:
                   df_input = "$HOME";
					break;
				case LOCALAPPDATA:
                   df_input = "/usr/local";
					break;
				case LOGONSERVER:
					break;
				case NUMBER_OF_PROCESSORS:
                   df_input = "$(nproc)";
					break;
				case OneDrive:
					break;
				case OneDriveConsumer:
					break;
				case OS:
                    df_input = "$(uname -s)";
					break;
				case Path:
                   df_input = "$PATH";
					break;
				case PATHEXT:
					break;
				case POWERSHELL_DISTRIBUTION_CHANNEL:
					break;
				case PROCESSOR_ARCHITECTURE:
                   df_input = "$(uname -p)";
					break;
				case PROCESSOR_IDENTIFIER:
                   df_input = "$(lscpu | grep \"Model name\"";
					break;
				case PROCESSOR_LEVEL:
                   df_input = "$(lscpu | grep \"CPU family\"";
					break;
				case PROCESSOR_REVISION:
					break;
                case ProgramData:
					df_input = "~/.config";
					break;				
				case ProgramFiles:
				case ProgramFilesx86:
				case ProgramW6432:
                   df_input = "/usr";
					break;
				case PROMPT_:
					break;
				case PSModulePath:
					break;
				case PUBLIC:
                   df_input = "$HOME";
					break;
				case SESSIONNAME:
                   df_input = "$STY";
					break;
				case SystemDrive:
                   df_input = "c";
					break;
				case SystemRoot:
                   df_input = "/";
					break;
				case TEMP:
				case TMP:
                   df_input = "/tmp";
					break;
				case USERDOMAIN:
				case USERDOMAIN_ROAMINGPROFILE:
                   df_input = "$(/usr/bin/domainname -a)";
					break;
				case USERNAME:
                   df_input = "$USER";
					break;
				case USERPROFILE:
                   df_input = "$HOME";
					break;
				case windir:
					break;
                   df_input = "/";
				case ZES_ENABLE_SYSMAN	:
					break;
				case TIME__:
                   df_input = "$(date +\"%T\")";
                   break;
				case RANDOM:
                  df_input = "$RANDOM";
					break;
				case ERRORLEVEL:
                   df_input = "$?";
					break;
				case DATE__:
                   df_input = "$(date +\"%D\")";
					break;
				case CMDCMDLINE:
					break;
				case CMDEXTVERSION:
                   df_input = "$SHELL --version";
					break;
				case CD__:
                   df_input = "$PWD";
					break;
                case -1:
                default:
					std::cout << "BUFFER_____: " << buffer<<std::endl;
					if(buffer.size() <= 2) {
						buffer = "$"+buffer.substr(1, buffer.size() -1);
					}
					else {
						buffer = "$"+buffer.substr(1, buffer.size() -2);
					}
					// std::cout << "Not a environmental variable: " << buffer << std::endl;
					df_input = "";
					break;
            }
			if(df_input != ""){
				// clear_previous(buffer, match);
				buffer = "";
				read_key_to_output(
					"VARIABLES", 
					VARIABLES[array_index].substr(1, VARIABLES[array_index].size() -2),
					df_input,	
					fd_variables.get(), 
					cts1, 
					buffer, 
					args->disable_atrc_warnings
				);
			}
			buffer_used = true;
		}

		revised_input += buffer;
		buffer = "";
		buffer_used = false;
    }
	input = revised_input;
}

