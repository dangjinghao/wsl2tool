#pragma once
#include <string>
#include<regex>
#include "CommandManager.h"
void TranslateToWSLPath(std::string& Argument);
void TranslateToWinPath(std::string& Argument);
extern std::string WSLApplicationPath;
extern std::string WinPrefix;