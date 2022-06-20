#pragma once
#include<Windows.h>
#include <fstream>
#include <iostream>
#include<string>
#include<regex>
extern std::string ApplicationPath;
extern std::string ApplicationFolderPath;
void InitConf();
std::string ReadConf(std::string section, std::string key);