#include"../include/wsl2tool.h"


void hello() {//TODO(command help)
	std::cout << "wsl2tool.exe" << std::endl;
	std::cout << " [wsl_command] [args][...]" << std::endl;
	std::cout << " ~ [action: create/delete/create_map] [...]" << std::endl;
	std::cout << "[action:create] [wsl_command] --- create linux command on windows " << std::endl;
	std::cout << "[action:create_map] [nickname] [wsl_command] --- create nickname of linux command on windows" << std::endl;
	std::cout << "[action:delete] [wsl_command/nickname] --- delete linux command by name or nickname " << std::endl;
}

int main(int argc, char* argv[]) {

	WSLApplicationPath = "wsl";
	WinPrefix = "/mnt/";//TODO file or sth to configure 
	ApplicationPath = argv[0];
	size_t LastSlashIndex = ApplicationPath.find_last_of(R"(\)");
	//e.g. C:\\test\\test\\ 
	ApplicationFolderPath = ApplicationPath.substr(0,LastSlashIndex+1);

	if (argc == 1) hello();
	else if (argv[1][0] == '~') {
		if (argc > 2) {
			std::string action = argv[2];
			if (action == "create") {
				CreateCmdFile(argv[3], argv[3]);
			}
			else if (action == "create_map") {
				CreateCmdFile(argv[3], argv[4]);
			}
			else if (action == "delete") {
				DeleteCmdFile(argv[3]);
			}
			else hello();

		}
		else hello();
	}else{
		std::string Arguments;
		for (int i = 1; i < argc; ++i) {
			std::string ArgumentBuffer = " " + std::string(argv[i]);
			TranslateToWSLPath(ArgumentBuffer);
			Arguments += ArgumentBuffer;
		}
		Command cmd;
		cmd.RunCommand(WSLApplicationPath + Arguments);
		std::string tmpResultString;
		std::vector<char> tmpResult,SolvedResult;

		for (auto c : cmd.Result) {
			if (c == '\0') {
				TranslateToWinPath(tmpResultString);
				tmpResult.assign(tmpResultString.begin(), tmpResultString.end());
				if (tmpResult.back() == '\0') tmpResult.pop_back();
				SolvedResult.insert(SolvedResult.end(), tmpResult.begin(),tmpResult.end());
				SolvedResult.push_back('\0');
				tmpResultString.clear();
			}
			else {
				tmpResultString.push_back(c);
			}
			
		}
		//SolvedResult.pop_back();
		cmd.Result.assign(SolvedResult.begin(), SolvedResult.end());
		cmd.PrintResult();
		

	}




}