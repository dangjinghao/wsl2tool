#pragma once
#include<iostream>
#include <vector>
class Command {
public:
	std::vector<char> Result = { '\0' };
	void RunCommand(const  std::string& cmdLine);
	void PrintResult();
	std::string GetStr();
};

