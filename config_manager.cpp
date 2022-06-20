#include"config_manager.h"

void InitConf() {
	std::string ConfFilePath = ApplicationFolderPath + "wsl2tool.ini";
	LPCTSTR ConfFile = ConfFilePath.c_str();

	WritePrivateProfileString(TEXT("windows"), TEXT("WinPrefix"), TEXT("/mnt/"), ConfFile);
	WritePrivateProfileString(TEXT("wsl2"), TEXT("WSLPath"), TEXT("wsl.exe"), ConfFile);
}

std::string ReadConf(std::string section, std::string key) {
	std::string ConfFilePath = ApplicationFolderPath + "wsl2tool.ini";
	LPCTSTR ConfFile = ConfFilePath.c_str();

	char content[100];
	DWORD v = ::GetPrivateProfileString(section.c_str(), key.c_str(), TEXT(""), content, 100, ConfFile);
	return std::string(content);
	
}