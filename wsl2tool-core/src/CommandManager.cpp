#include"../include/CommandManager.h"

void Command::RunCommand(const  std::string& cmdLine) {
	char buffer[1024] = { 0 };
	FILE* ptrFile = NULL;
	ptrFile = _popen((cmdLine).c_str(), "r");
	if (ptrFile == NULL) {
		std::cerr << "open pipe failed" << std::endl;
		this->Result= {'\0'};
	}

	std::vector<char> ret;
	int BufferCount = 0;
	do {
		
		BufferCount = fread(buffer, sizeof(char), 1023, ptrFile);
		for (char* BufferPtr = buffer; BufferPtr < buffer + BufferCount;
			BufferPtr = BufferPtr + strlen(BufferPtr) + 1)
		{
			std::string tempBufferString = BufferPtr;
			ret.insert(ret.end(),tempBufferString.begin(), tempBufferString.end());
			ret.insert(ret.end(), '\0');
		}
		memset(buffer, 0, 1024);

	} while (BufferCount == 1023);

	_pclose(ptrFile);
	this->Result= ret;
}

void Command::PrintResult() {
	if (this->Result.size())
		for (int c = 0; c < (this->Result.size() - 1); c++) {
			putchar(this->Result[c]);
		}
}

std::string Command::GetStr() {

	std::string CmdResultString;
	CmdResultString.insert(CmdResultString.begin(), this->Result.begin(), this->Result.end());
	return CmdResultString;

}