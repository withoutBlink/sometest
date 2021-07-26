#ifndef HARDWAREFREAK_H
#define HARDWAREFREAK_H

#include <map>
#include <vector>
#include <string>

namespace HardwareFreak
{
    std::string GetOSDevNode();
    std::string GetHdSN(const std::string& devnode = "");
    std::string GetHdFwRecv(const std::string& devnode = "");

    int NetworkInterfaceSpeedCmp(const std::string& interface, unsigned short speedmode);
    std::string GetNetworkRoute(const std::string& interface);
    std::vector<std::string> GetNetworkInterface();
    /**
     * @brief GetNetworkList - 获取IP与mask地址
     * @return  获取IP与mask地址的Map
     */
    std::map<int, std::string> GetNetworkList();
};

#endif // HARDWAREFREAK_H
