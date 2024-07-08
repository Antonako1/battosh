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

void quicker_read(std::string key, std::string original_value, std::vector<std::string> inserts, std::string &output, battosh_info *fd){
	std::string cts="";
	read_key_to_output("VARIABLES", key, original_value, fd_variables.get(), output, fd->disable_atrc_warnings);
	InsertVar(output, inserts, fd_variables.get());
};

std::tuple<int, int> check_for_full_var_matches(std::string &buffer){
	for(int i = 0; i < sizeof(VARIABLES)/sizeof(VARIABLES[0]); i+=2){
        if(buffer == VARIABLES[i]){
			// std::cout << buffer << " : " << VARIABLES[i] << " : " << i << " : " << std::stoi(VARIABLES[i+1]) << std::endl;
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
		write_to_output_log("Variable found.");
		buffer += ahead;
		index++;
		ahead = look_ahead(index, input);
		if(ahead == '%'){ // look for %%x
			write_to_output_log("Recognized as %%x");
		    buffer += ahead;
			index++;
			ahead = look_ahead(index, input);
			buffer += ahead;
			//buffer contains %%x
			buffer_used = true;
		}
		
		if(!buffer_used && ahead == '~'){
			write_to_output_log("Recognized as percent tilde, %~x");
			bool ptd = false;
			bool ptp = false;
			bool ptn = false;
			bool ptx = false;
			while(!std::isdigit(ahead)){
				ahead = look_ahead(index, input);
				buffer += ahead;
				if(ahead == 'd') ptd = true;
				if(ahead == 'p') ptp = true;
				if(ahead == 'n') ptn = true;
				if(ahead == 'x') ptx = true;
				index++;
			}
			ahead = look_ahead(index, input);
			buffer += ahead;
			// buffer contains %~(d|p|n|x)<single_digit>
			std::string num = "$" + buffer.substr(buffer.size() - 2, 1);
			std::string temp_buffer = "";
			std::vector<std::string> inserts = {num};
			std::string common_dpnx = "";
			read_variable_to_output("common_dpnx", "$(dirname %*0%)/$(basename %*0%)", fd_variables.get(), common_dpnx, args->disable_atrc_warnings);
			
			if		(ptd) quicker_read("cd_d", "$(dirname %*%)", inserts, temp_buffer, args);
			else if	(ptp) quicker_read("cd_p", "$(dirname %*%)", inserts, temp_buffer, args);
			else if	(ptn) quicker_read("cd_n", "$(filename %*%)", inserts, temp_buffer, args);
			else if	(ptx) quicker_read("cd_x", "", inserts, temp_buffer, args);
			else if	(ptd && ptp) quicker_read("cd_dp", "$(dirname %*%)", inserts, temp_buffer, args);
			else if	(ptd && ptn) quicker_read("cd_dn", common_dpnx, inserts, temp_buffer, args);
			else if	(ptd && ptx) quicker_read("cd_dx", "", inserts, temp_buffer, args);
			else if	(ptp && ptn) quicker_read("cd_pn", common_dpnx, inserts, temp_buffer, args);
			else if	(ptp && ptx) quicker_read("cd_px", "", inserts, temp_buffer, args);
			else if	(ptn && ptx) quicker_read("cd_nx", common_dpnx, inserts, temp_buffer, args);
			else if	(ptd && ptp & ptn) quicker_read("cd_dpn", common_dpnx, inserts, temp_buffer, args);
			else if	(ptd && ptn & ptx) quicker_read("cd_dnx", common_dpnx, inserts, temp_buffer, args);
			else if	(ptd && ptp & ptx) quicker_read("cd_dpx", "", inserts, temp_buffer, args);
			else if	(ptn && ptp & ptx) quicker_read("cd_npx", common_dpnx, inserts, temp_buffer, args);
			else if (ptn && ptp && ptn && ptx) quicker_read("cd_dpnx", common_dpnx, inserts, temp_buffer, args);
			else {
				// TODO ERROR MESSAGE
				std::cout << "Error with percent tilde" << std::endl;
			}
			buffer_used = true;
			buffer = temp_buffer;
		}
		// TODO check for percent colon and output

		if(!buffer_used){
			write_to_output_log("Recognized as 	%x% or %[0-9]");
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
			
			//buffer contains %x% or %[0-9]
			else {
				const std::tuple results_ = check_for_full_var_matches(buffer);
				array_index = std::get<0>(results_);
				match = std::get<1>(results_);
			}

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
					if(buffer.size() <= 2) {
						buffer = "$"+buffer.substr(1, buffer.size() -1);
					}
					else {
						buffer = "$"+buffer.substr(1, buffer.size() -2);
					}
					df_input = "";
					break;
            }
			if(df_input != ""){
				buffer = "";
				read_key_to_output(
					"VARIABLES", 
					VARIABLES[array_index].substr(1, VARIABLES[array_index].size() -2),
					df_input,	
					fd_variables.get(), 
					buffer, 
					args->disable_atrc_warnings
				);
			}
			buffer_used = true;
		}

		revised_input += buffer;
		write_to_output_log("Tinkered variable: " + buffer);
		buffer = "";
		buffer_used = false;
    }
	input = revised_input;
}

