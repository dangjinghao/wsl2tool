#include"command_manager.h"
#pragma warning(disable:4996)
std::string CmdPopen( std::string& cmdLine) {
	char buffer[1024] = { 0 };
	FILE* ptrFile = NULL;
	ptrFile = _popen((cmdLine).c_str(), "r");
	if (ptrFile == NULL) {
		std::cerr << "open pipe failed" << std::endl;
		return std::string("");

	}
	std::string ret;
 	while (fgets(buffer, sizeof(buffer), ptrFile)!=NULL)
		std::cout<<buffer;
	_pclose(ptrFile);
	return ret;
}

