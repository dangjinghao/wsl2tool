#include <string>
#include<Windows.h>
class Config {
public:
	std::string ConfigFilePath;
	std::string Read(std::string Section, std::string Key);
	bool CreateFile();

};
bool Config::CreateFile() {
	WritePrivateProfileString(TEXT("windows"), TEXT("WinPrefix"), TEXT("/mnt/"), ConfigFilePath.c_str());
	WritePrivateProfileString(TEXT("wsl2"), TEXT("WSLPath"), TEXT("wsl.exe"), ConfigFilePath.c_str());
	return true;
}

std::string Config::Read(std::string Section, std::string Key) {
	char Content[256]={0};
	DWORD ContentCount = GetPrivateProfileStringA(Section.c_str(), Key.c_str(), TEXT(""), Content, 256, ConfigFilePath.c_str());
	return std::string(Content);
}


