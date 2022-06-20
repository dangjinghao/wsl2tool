#pragma once
#include<fstream>
#include <string>


extern  std::string ApplicationPath;
extern std::string ApplicationFolderPath;
int DeleteCmdFile( const std::string WindowsCmdName);
int CreateCmdFile( const std::string WindowsCmdName, const std::string LinuxCmdName);