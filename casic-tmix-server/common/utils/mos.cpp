/*
* @Author:  徐哲阳
* @EMail:   xuzheyangchn@foxmail.com
* @FileName:utils.cpp
* @Created: 2020-03-09 07:08:57
* @Description: 
*/
#include "mos.h"

#include "mstring.h"

#if defined (KOS) && defined (SERVER)
#include <rpm/rpmts.h>
#include <rpm/rpmdb.h>
#include <rpm/rpmlib.h>
#endif

std::string MOS::GetCurTime()
{
    time_t now;
    struct tm *timenow;
    time(&now);
    char strtime[100] = {};
    timenow = localtime(&now);
    strftime(strtime, 100, "%Y-%m-%d", timenow);

    std::string time_str = strtime;
    return time_str;
}

void MOS::Delayed(int seconds, int useconds)
{
    struct timeval time;
    time.tv_sec = seconds;
    time.tv_usec = useconds;
    select(0, nullptr, nullptr, nullptr, &time);
}

std::string MOS::ShellCmd(const std::string &cmd)
{
    std::string result;

    do {
        FILE *fp = popen(cmd.c_str(), "r");
        if (!fp) {
            break;
        }

        while (!feof(fp)) {
            char buf[1024] = {0};
            size_t len = fread(buf, 1, sizeof (buf), fp);
            if (len > 0)
                result += std::string(buf, len);
        }

        pclose(fp);
    } while(false);

    return result;
}

std::string MOS::GetPackageVer(const std::string &packname)
{
    std::string ver;
    do {
#if defined (KOS) && defined (SERVER)
	int status = rpmReadConfigFiles(nullptr, nullptr);
	if (status != 0) {
	    printf("Error reading RC files.\n");
	    break;
	}

	rpmts ts;
	rpmdbMatchIterator iter = nullptr;
	Header header = nullptr;

	ts = rpmtsCreate();
	iter = rpmtsInitIterator(ts, RPMTAG_NAME, packname.c_str(), packname.length());
	while ( (header = rpmdbNextIterator(iter) ) != nullptr) {
	    ver = std::string(headerGetString(header, RPMTAG_VERSION))
		    + "-"
		    + std::string(headerGetString(header, RPMTAG_RELEASE));
	}

	rpmdbFreeIterator(iter);
	rpmtsFree(ts);
	rpmFreeRpmrc();
#else
        char cmd[1024] = {'\0'};
	std::sprintf(cmd, "dpkg -l %s* | grep %s | awk -F ' ' '{print $3}'", packname.c_str(), packname.c_str());
        ver = MOS::ShellCmd(cmd);
	MString::Trim(ver, '\n');
#endif
    } while (false);
    return ver;
}
