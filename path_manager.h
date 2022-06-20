#pragma once
#include <string>
#include<regex>
#include <iostream>

void ReplaceAll(std::string& BaseString, std::string const& OldVal, std::string const& NewVal);
void TranslateToWsl(std::string& ArgumentString);
void TranslateToWin(std::string& CmdStdout);
