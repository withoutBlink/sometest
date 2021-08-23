#include "hardwarefreak.h"

#include "mstring.h"

#include <fstream>

#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/hdreg.h>

#include <ifaddrs.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <net/if.h>

#include <linux/ethtool.h>
#include <linux/sockios.h>

/* hack, so we may include kernel's ethtool.h */
//typedef unsigned long long __u64;
typedef __uint32_t __u32;       /* ditto */
typedef __uint16_t __u16;       /* ditto */
typedef __uint8_t __u8;         /* ditto */


std::string HardwareFreak::GetOSDevNode()
{
    std::ifstream in("/proc/mounts");
    std::string line;

    std::string osdevnode;

    while (getline(in, line)) {
        MString::Trim(line, ' ');
        std::vector<std::string> list = MString::SplitString(line, " ");
        for (int i = 0; i < static_cast<int>(list.size()); i++) {
            if (!MString::StartsWith(list.at(0), "/dev")) {
                continue;
            }

            if (list.at(1) == "/") {
                osdevnode = list.at(0);
                break;
            }
        }

        if (!osdevnode.empty())
            break;
    }

    return osdevnode;
}

std::string HardwareFreak::GetHdSN(const std::string &devnode)
{
    std::string dev = devnode.empty() ? GetOSDevNode() : devnode;
    if (dev.empty()) {
        return "";
    }

    int fd = open (dev.c_str(), O_RDONLY);
    if (fd < 0) {
        return "";
    }

    struct hd_driveid hid;
    if (ioctl (fd, HDIO_GET_IDENTITY, &hid) < 0) {
        return "";
    }
    close (fd);

    size_t argsize = sizeof(hid.serial_no);
    size_t strsize = strlen(reinterpret_cast<const char*>(hid.serial_no));

    return std::string(reinterpret_cast<const char*>(hid.serial_no), argsize < strsize ? argsize : strsize);
}

std::string HardwareFreak::GetHdFwRecv(const std::string &devnode)
{
    std::string dev = devnode.empty() ? GetOSDevNode() : devnode;
    if (dev.empty()) {
        return "";
    }

    int fd = open (dev.c_str(), O_RDONLY);
    if (fd < 0) {
        return "";
    }

    struct hd_driveid hid;
    if (ioctl (fd, HDIO_GET_IDENTITY, &hid) < 0) {
        return "";
    }
    close (fd);

    size_t argsize = sizeof(hid.fw_rev);
    size_t strsize = strlen(reinterpret_cast<const char*>(hid.fw_rev));

    return std::string(reinterpret_cast<const char*>(hid.fw_rev), argsize < strsize ? argsize : strsize);
}


std::vector<std::string> HardwareFreak::GetNetworkInterface()
{
    std::vector<std::string> interface;
    int fd = 0;

    do {
        int interfaceNum = 0;
        struct ifreq buf[16];
        struct ifconf ifc;

        if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            break;
        }

        ifc.ifc_len = sizeof(buf);
        ifc.ifc_buf = (caddr_t)buf;
        if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc)) {
            interfaceNum = ifc.ifc_len / sizeof(struct ifreq);
            while (interfaceNum-- > 0) {
                if (strcmp(buf[interfaceNum].ifr_name, "lo") == 0)
                    continue;

                struct ifreq ifr;
                int skfd = socket(AF_INET, SOCK_DGRAM, 0);

                strcpy(ifr.ifr_name, buf[interfaceNum].ifr_name);
                if (ioctl(skfd, SIOCGIFFLAGS, &ifr) < 0) {
                    continue;
                }

                if(ifr.ifr_flags & IFF_RUNNING)
                    interface.push_back(buf[interfaceNum].ifr_name);
                //                    printf("ndevice name: %s\n", buf[interfaceNum].ifr_name);
            }
        }
    } while (false);

    if (fd)
        close (fd);

    return interface;
}


std::map<int, std::string> HardwareFreak::GetNetworkList()
{
    std::map<int, std::string> networkMap;
    struct ifaddrs * ifAddrStruct = nullptr;
    void * tmpAddrPtr = nullptr;

    getifaddrs(&ifAddrStruct);

    while (ifAddrStruct != nullptr) {
        if (ifAddrStruct->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr = &(reinterpret_cast<struct sockaddr_in *>(ifAddrStruct->ifa_addr))->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN] = {0};
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            if (strcasecmp(addressBuffer, "127.0.0.1") == 0) {
                continue;
            }

            uint32_t uint32mask = (reinterpret_cast<struct sockaddr_in *>(ifAddrStruct->ifa_addr))->sin_addr.s_addr;
            int i = 0;
            while ((uint32mask >> i) & 0x01) {
                i++;
            }

            networkMap[i / 8] = addressBuffer;
        }
        ifAddrStruct=ifAddrStruct->ifa_next;
    }

    return networkMap;
}

int HardwareFreak::NetworkInterfaceSpeedCmp(const std::string &interface, unsigned short speedmode)
{
    struct ifreq ifr;
    int fd;

    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name, interface.c_str());

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        return -1;
    }

    int err;
    struct ethtool_cmd ep;

    ep.cmd = ETHTOOL_GSET;
    ifr.ifr_data = (caddr_t)&ep;
    err = ioctl(fd, SIOCETHTOOL, &ifr);
    if (err != 0) {
        return -1;
    }

    return ep.speed - speedmode;
}


std::string HardwareFreak::GetNetworkRoute(const std::string &interface)
{
    std::string networkroute;
    int fd = 0;

    do {
        int interfaceNum = 0;
        struct ifreq buf[16];
        struct ifconf ifc;

        if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            break;
        }

        ifc.ifc_len = sizeof(buf);
        ifc.ifc_buf = (caddr_t)buf;
        if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc)) {
            interfaceNum = ifc.ifc_len / sizeof(struct ifreq);
            while (interfaceNum-- > 0) {
                if (strcmp(buf[interfaceNum].ifr_name, "lo") == 0)
                    continue;

                struct ifreq ifr;
                int skfd = socket(AF_INET, SOCK_DGRAM, 0);

                strcpy(ifr.ifr_name, buf[interfaceNum].ifr_name);
                if (ioctl(skfd, SIOCGIFFLAGS, &ifr) < 0) {
                    continue;
                }

                if(ifr.ifr_flags & IFF_RUNNING)
                    networkroute;
            }
        }
    } while (false);

    if (fd)
        close (fd);

    return networkroute;
}
