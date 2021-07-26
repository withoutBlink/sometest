#ifndef MOS_H
#define MOS_H

#include <string>

namespace MOS {
    std::string GetCurTime();
    void Delayed(int seconds, int useconds = 0);
    std::string ShellCmd(const std::string& cmd);
    std::string GetPackageVer(const std::string& packname);
}


#endif // MOS_H
