#ifndef SOFTWAREABOUT_H
#define SOFTWAREABOUT_H

#define SOFTWARE_TITLE			"T-Mix"
#define SOFTWARE_YEAR			"2021"
#define SOFTWARE_VERSION		"3.0.1"
#define SOFTWARE_COPYRIGHT		"Copyright©" SOFTWARE_YEAR " 北京计算机技术及应用研究所."
#define SOFTWARE_COMPANY		"航天七〇六"

#define IP_SERVICE			"127.0.0.1"

#define PORT_SCANSRV			7061
#define PORT_SERVER_HTTP		7062
#define PORT_SERVER_WS			7063
#define PORT_SERVICE			7064

#define WS_URL_SVC			"127.0.0.1:7064"
#define WS_URL_SVCUI			"/tmix/ui"
#define WS_URL_SVCITEMS			"/tmix/items"

#define WS_URL_UI			WS_URL_SVC WS_URL_SVCUI
#define WS_URL_ITEMS			WS_URL_SVC WS_URL_SVCITEMS

#define SOFTWARE_PATH			"/home/ht706/casic-tmix/build-casic-tmix-server-Desktop_Qt_5_13_1_GCC_64bit-Release"
#define SOFTWARE_PATH_BIN		SOFTWARE_PATH "/bin"

#define SOFTWARE_PATH_LOG		SOFTWARE_PATH "/logs"
#define SOFTWARE_PATH_LOG_MAINUI	SOFTWARE_PATH_LOG "/ui-%datetime{%Y%M%d}.log"
#define SOFTWARE_PATH_LOG_SERVICE	SOFTWARE_PATH_LOG "/svc-%datetime{%Y%M%d}.log"
#define SOFTWARE_PATH_LOG_TESTITEM	SOFTWARE_PATH_LOG "/items-%datetime{%Y%M%d}.log"

#define SOFTWARE_PATH_CONFIG		SOFTWARE_PATH "/config/tmix.conf"
#define SOFTWARE_PATH_DB		SOFTWARE_PATH "/config/tmix.sqlite3"
#define SOFTWARE_CMD_FINDCOMMAND	"Find Srv Command."

#define SYSTEM_CONF_INFO                "/etc/.systeminfo"
#define IDINT                           u_int32_t

#endif // SOFTWAREABOUT_H
