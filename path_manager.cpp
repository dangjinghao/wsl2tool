#include"config_manager.h"

int inline IsUpper(char c) {
    if (c >= 'A' && c <= 'Z') return 1;
    return 0;
}


void ReplaceAll(std::string& BaseString, std::string const& OldVal, std::string const& NewVal)
{
    std::string::size_type pos = BaseString.find(OldVal), t_size = OldVal.size(), r_size = NewVal.size();
    while (pos != std::string::npos) { // found   
        BaseString.replace(pos, t_size, NewVal);
        pos = BaseString.find(OldVal, pos + r_size);
    }
}


void TranslateToWsl(std::string &ArgumentString) {
    //translate windwos path
    std::string WinPrefix = ReadConf("wsl2", "WinPrefix");
    //std::string WslCoreVersion = ReadConf("wsl2", "LinuxCoreVer");
    if (WinPrefix == "") WinPrefix = "/mnt/";
    //if (WslCoreVersion == "") WslCoreVersion = "5.10";
    std::regex WinPath(R"(\W\w:\\[^! :<>?|']+)");
    std::sregex_iterator RegexIterEnd;
    std::string TempArgumentString = ArgumentString;
    for (std::sregex_iterator iter(ArgumentString.begin(), ArgumentString.end(), WinPath);
    iter != RegexIterEnd; iter++) {
        std::smatch match = *iter;
        std::string TempWinPath = match.str();
        TempWinPath[1] = IsUpper(TempWinPath[1]) ? TempWinPath[1] + 32 : TempWinPath[1];
        TempWinPath.erase(2,1);
        TempWinPath.insert(1, WinPrefix);
        ReplaceAll(TempWinPath, "\\", "/");

        ReplaceAll(TempArgumentString, match.str(), TempWinPath);

    }

    //translate () in refer
    if (!(TempArgumentString[1] == '"' && TempArgumentString.back() == '"' ||
        TempArgumentString[1] == '\'' && TempArgumentString.back() == '\''
        ) ){
        ReplaceAll(TempArgumentString, "(", R"(\()");
        ReplaceAll(TempArgumentString, ")", R"(\))");

    }

    ArgumentString = TempArgumentString;
}

void TranslateToWin(std::string& CmdStdout) {
    std::string WinPrefix = ReadConf("wsl2", "WinPrefix");
        if (WinPrefix == "") WinPrefix = "/mnt/";
        std::regex WinOnLinuxPath(WinPrefix+R"(\w/[^! :<>?|']+)");
        std::sregex_iterator RegexIterEnd;
        std::string TempCmdStdout=CmdStdout;
        for (std::sregex_iterator iter(CmdStdout.begin(), CmdStdout.end(), WinOnLinuxPath);
            iter != RegexIterEnd; iter++) {
            std::smatch match = *iter;
            std::string TempLinuxPath = match.str();
            ReplaceAll(TempLinuxPath, WinPrefix, "");
            TempLinuxPath[0] = TempLinuxPath[0] - 32;
            TempLinuxPath.insert(1,":");
            ReplaceAll(TempLinuxPath, "/", "\\");
            ReplaceAll(TempCmdStdout, match.str(), TempLinuxPath);

        }
        CmdStdout = TempCmdStdout;

}