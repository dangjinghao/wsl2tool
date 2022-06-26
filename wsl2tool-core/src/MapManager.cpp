#include"../include/MapManager.h"


int CreateCmdFile(const std::string WindowsCmdName, const std::string LinuxCmdName) {
	std::ofstream ofs;
	ofs.open(ApplicationFolderPath + WindowsCmdName + ".cmd", std::ios::out);
	ofs << "@echo off" << std::endl;
	ofs << ApplicationPath + " " + LinuxCmdName + " %*" << std::endl;
	return 0;

}

int DeleteCmdFile(const std::string WindowsCmdName) {
	remove(std::string(ApplicationFolderPath + WindowsCmdName + ".cmd").c_str());
	return 0;

}