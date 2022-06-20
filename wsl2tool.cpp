#include <string>
#include <iostream>
#include"path_manager.h"
#include "config_manager.h"
#include "map_manager.h"
#include "command_manager.h"
std::string ApplicationPath;
std::string ApplicationFolderPath;


int hello() {//TODO(ÕÍ…∆command tip)
	std::cout << "wsl2tool.exe" << std::endl;
	std::cout << " [linux_command] [args][...] ---call the wsl command" << std::endl;
	std::cout << " ~ [action:create/delete/create_map/init_conf] [args][...]" << std::endl;
	std::cout << "[action:create] [linux_cmd]---create linux command on windows " << std::endl;
	std::cout << "[action:create_map] [nickname] [linux_cmd] ---create nickname of linux command on windows" << std::endl;
	std::cout << "[action:delete] [Linux_cmd/nickname]---delete linux command by name or nickname " << std::endl;
	std::cout << "[action:init_conf] ---create configure file" << std::endl;

	return 0;
}
int main(int argc,char* argv[]) {
	ApplicationPath = argv[0];
	auto index = ApplicationPath.find_last_of("\\");
	ApplicationFolderPath = ApplicationPath.substr(0, index + 1);
	std::string WSLRunPath = ReadConf("wsl2", "WSLPath");
	if (WSLRunPath == "") WSLRunPath = "wsl.exe";
	if (argc==1) hello();
	else if (argv[1][0] == '~') {
		if (argc > 2) {
			std::string action = argv[2];
			if (action == "create") {
				CreateCmdFile( argv[3], argv[3]);
			}
			else if (action == "create_map") {
				CreateCmdFile( argv[3], argv[4]);
			}
			else if (action == "delete") {
				DeleteCmdFile(argv[3]);
			}
			else if (action == "init_conf") {
				InitConf();
			}
			else hello();

		}
		else hello();
		
	}
	else {
		std::string ArgumentString;
	
		for (int i = 1; i < argc; i++) {
			std::string tmpArgument = " " + std::string(argv[i]);
			TranslateToWsl(tmpArgument);
			ArgumentString.append(tmpArgument);
		}
		
		WSLRunPath.append(ArgumentString);
		//std::string CmdResult=CmdPopen(WSLRunPath);
		system(WSLRunPath.c_str());
		//TranslateToWin(WSLRunPath);
		//std::cout << std::endl<<WSLRunPath ;
	}
	return 0;
}
