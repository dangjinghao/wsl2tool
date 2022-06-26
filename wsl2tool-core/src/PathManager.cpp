#include "../include/PathManager.h"

int inline IsUpper(char c) {
	if (c >= 'A' && c <= 'Z') return 1;
	return 0;
}

void ReplaceAll(std::string& BaseString, std::string const& OldVal, std::string const& NewVal)
{
	std::string::size_type pos = BaseString.find(OldVal), t_size = OldVal.size(), r_size = NewVal.size();
	while (pos != std::string::npos) {
		BaseString.replace(pos, t_size, NewVal);
		pos = BaseString.find(OldVal, pos + r_size);
	}
}
void inline TranslateWithDoubleQuotation(std::string& Argument) {
	//TODO TranslateWithDoubleQuotation doesn`t work
	std::regex WindowsPathWithQuotation(R"( \"\w:\\.*\")");
	std::regex_replace(Argument, WindowsPathWithQuotation, "`"+WSLApplicationPath+" wslpath");

}


void TranslateToWSLPath(std::string& Argument) {
	if (Argument[1] == '"' && Argument.back() == '"') {
		//TODO doesn`t work
		//TranslateWithDoubleQuotation(Argument);
	}
	else {
		std::regex WindowsPathNoQuotation(R"(\W\w:\\[^! :<>?|']+)");
		std::sregex_iterator RegexIterEnd;
		std::string ArgumentString = Argument;
		for (std::sregex_iterator iter(Argument.begin(), Argument.end(), WindowsPathNoQuotation);
			iter != RegexIterEnd; iter++) {
			std::string WinPathBuffer = iter->str();

			//"xxx `wslcmd '/path/to/'`"
			WinPathBuffer.insert(1, "`wslpath '");
			WinPathBuffer += "'`";

			ReplaceAll(ArgumentString, iter->str(), WinPathBuffer);
			

		}
		ReplaceAll(ArgumentString, "(", "\\(");
		ReplaceAll(ArgumentString, ")", "\\)");

		Argument = ArgumentString;
	}
}
void TranslateToWinPath(std::string& CmdStdout) {

	std::regex WinOnLinuxPath(WinPrefix + R"(\w/[^! :<>?|']+)");
	std::sregex_iterator RegexIterEnd;
	std::string TempCmdStdout = CmdStdout;
	for (std::sregex_iterator iter(CmdStdout.begin(), CmdStdout.end(), WinOnLinuxPath);
		iter != RegexIterEnd; iter++) {
		std::string TempLinuxPath = iter->str();

		TempLinuxPath.insert(0, WSLApplicationPath+" wslpath -w ");
		Command cmd;
		cmd.RunCommand(TempLinuxPath);
		std::string CmdResultString = cmd.GetStr();
		ReplaceAll(TempCmdStdout, iter->str(), CmdResultString);
	}
	
	CmdStdout = TempCmdStdout;

}