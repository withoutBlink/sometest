#include "worker.h"

#ifdef __cplusplus
extern "C"  {
#endif

#include <fcntl.h>
#include <mntent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <net/if.h>
//#include <ifaddrs.h>
#include <scsi/sg.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
//#include <arpa/inet.h>
#include <linux/hdreg.h>
#include <scsi/scsi_ioctl.h>
//#include <linux/ethtool.h>
//#include <linux/sockios.h>

#ifdef __cplusplus
}
#endif

#include "utils/softwareabout.h"
#include "utils/hardwarefreak.h"

#include "fmt/format.h"
#include "inifile/inifile.h"
#include "nlohmann/json.hpp"
#include "easylog/easylogging++.h"

#include "asynctimerqueue.hh"

Worker *Worker::_This = nullptr;

Worker *Worker::Instance()
{
	if (!_This) {
		_This = new Worker;
	}
	return _This;
}

void Worker::Destory()
{
	if (_This) {
		delete _This;
		_This = nullptr;
	}
}

Worker::Worker()
	: _CurDialogId(0)
{

}

Worker::~Worker()
{

}

void Worker::callInput(const std::string &title, const std::string &text, const std::string& validator)
{
	// InputBox
	std::srand((unsigned)std::time(NULL));
	this->_CurDialogId = std::rand();
	nlohmann::json json;
	json["Method"] = "SendCallUI";
	json["Content"]["Id"] = this->_CurDialogId;
	json["Content"]["Type"] = "InputBox";
	if (!title.empty()) {
		json["Content"]["Title"] = title;
	}
	if (!text.empty()) {
		json["Content"]["Text"] = text;
	}
	if (!validator.empty()) {
		json["Content"]["Validator"] = validator;
	}
	this->sendMessage(json);
}

std::string Worker::recvInput(const nlohmann::json &msg)
{
	return msg["Msg"].get<std::string>();
}

void Worker::sendMessage(const nlohmann::json &message)
{
	if (message.empty()) {
		return ;
	}

	LOG(INFO) << "Client: Sending message: \n" << message.dump(4) << "\n";

	auto send_stream = std::make_shared<WsClient::SendStream>();
	*send_stream << message.dump();
	this->_Connection->send(send_stream);
}

std::string Worker::getValueFromConf(const std::string &key)
{
	std::string value;

	do {
		inifile::IniFile inifile;
		if (inifile.Load(SYSTEM_CONF_INFO)) {
			LOG(ERROR) << inifile.GetErrMsg();
			break;
		}

		std::string _group = key.substr(0, key.find_first_of("-"));
		std::string _key = key.substr(key.find_first_of("-") + 1);

		if (inifile.GetStringValue(_group, _key, &value)) {
			LOG(ERROR) << inifile.GetErrMsg();
			value.clear();
			break;
		}

	} while (false);

	return value;
}

std::string Worker::getBHDC()
{
	std::string bhdc = getBHDC("/dev/sda");
	if (bhdc.find("bhdc") == std::string::npos) {
		bhdc = getBHDC("/dev/sdb");
		if (bhdc.find("bhdc") == std::string::npos) {
			bhdc.clear();
		}
	}
	return bhdc;
}

std::string Worker::getBHDC(const std::string &devnode)
{
	int fd = -1;
	std::string version;
	struct sg_io_hdr * p_hdr = nullptr;

	try {
		//初始化p_hdr
		p_hdr = (struct sg_io_hdr *)malloc(sizeof(struct sg_io_hdr));
		memset(p_hdr, 0, sizeof(struct sg_io_hdr));

		p_hdr->interface_id = 'S';
		p_hdr->flags = SG_FLAG_LUN_INHIBIT;

		//设置传输数据buffer
		unsigned char data_buffer[32/*BLOCK_LEN*/ * 256];
		p_hdr->dxferp = data_buffer;
		p_hdr->dxfer_len = 32 * 256;

		//设置sense buffer
		unsigned char sense_buffer[255/*SENSE_LEN*/];
		p_hdr->sbp = sense_buffer;
		p_hdr->mx_sb_len = 255;

		LOG(INFO) << fmt::format("the device name: {0}", devnode);

		fd = open(devnode.c_str(), O_RDWR);
		if (fd < 0) {
			throw std::invalid_argument("failed open sg file " + devnode);
		}

		unsigned char cdb[12] = {
			0xa1, 0x08, 0x02, 0, 0x01, 0, 0, 0, 0, 0xc9, 0, 0
		};

		p_hdr->dxfer_direction = SG_DXFER_FROM_DEV;
		p_hdr->cmdp = cdb;
		p_hdr->cmd_len = 12;

		if (ioctl(fd, SG_IO, p_hdr) < 0) {
			throw std::invalid_argument("failed SCSI command.");
		}

		if (p_hdr->status == 0) {
			char *buffer = reinterpret_cast<char *>(p_hdr->dxferp);
			version = std::string(buffer, 12);
		} else {
			throw std::invalid_argument("failed bhdc version.");
		}
	} catch (std::exception& e) {
		LOG(ERROR) << e.what();
	}

	if (fd > 0)
		close(fd);

	if (p_hdr)
		free(p_hdr);

	return version;
}

std::string Worker::findDevNode(const std::string &mountpoint)
{
	std::string osdevnode;
	FILE *file = nullptr;
	do {
		file = setmntent("/proc/mounts", "r");
		if (!file) {
			break;
		}

		struct mntent *mnt = nullptr;
		while ((mnt = getmntent(file)) != nullptr) {
			if (std::string(mnt->mnt_dir) == mountpoint) {
				osdevnode = std::string(mnt->mnt_fsname);
				break;
			}
		}

	} while (false);

	if (file) {
		endmntent(file);
	}

	return osdevnode;
}

std::string Worker::getOSDevNode()
{
	return findDevNode("/boot");
}

std::string Worker::getHomeDevNode()
{
	return findDevNode("/home");
}

std::string Worker::getHdFwRecv()
{
	int fd = 0;
	struct hd_driveid hid;
	do {
		std::string dev = getOSDevNode();
		if (dev.empty()) {
			return "";
		}

		fd = open (dev.c_str(), O_RDONLY);
		if (fd < 0) {
			return "";
		}

		if (ioctl (fd, HDIO_GET_IDENTITY, &hid) < 0) {
			return "";
		}
	} while (false);

	if (fd)
		close (fd);

	return std::string(reinterpret_cast<const char*>(hid.fw_rev), sizeof(hid.fw_rev));
}

std::string Worker::shellCmd(const std::string &cmd)
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

std::string Worker::getPackageVer(const std::string &packname)
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
        ver = shellCmd(cmd);
        ver = ver.substr(0, ver.find_last_not_of("\n"));
#endif
    } while (false);
    return ver;
}

void Worker::Start(std::shared_ptr<WsClient::Connection> connection)
{
    this->_Connection = connection;

    nlohmann::json json = {
        { "Method", "ItemConf" },
        { "Content", "" }
    };

    this->sendMessage(json);
}

void Worker::Config(const nlohmann::json &msg)
{
    try {
        this->_CurItemConf = msg;
        LOG(DEBUG) << msg.dump(4);

        nlohmann::json json;
        nlohmann::json result = {
            { "Method", "ItemResult" }
        };
        json["Method"] = "Messages";
        json["Content"]["Msg"] = "测试项：" + msg["Name"].get<std::string>();
        this->sendMessage(json);

        std::string standard = msg["Standard"].get<std::string>();
        json["Content"]["Msg"] = "通过标准：<span style='color:green'>" + standard + "</span>";
        this->sendMessage(json);

        if (msg["Args"].get<std::string>() == "FwRecv") {
            std::string value = getHdFwRecv();
            if (standard.compare(value) == 0) {
                result["Content"]["Code"] = true;
                result["Content"]["Msg"] = "符合预期值";
                json["Content"]["Msg"] = "当前获取值：<span style='color:green'>" + value + "</span><br>测试结果：符合预期值<br>";
            } else {
                result["Content"]["Code"] = false;
                result["Content"]["Msg"] = fmt::format("当前值{0}：与预期值不符", value);
                json["Content"]["Msg"] = "当前获取值：<span style='color:red'>" + (value.empty() ? "未获取到当前值" : value) + "</span><br>测试结果：与预期值不符<br>";
			}
			this->sendMessage(json);
			this->sendMessage(result);

		} else if (msg["Args"].get<std::string>() == "Tipterminal") {
            std::string value = getPackageVer("tipterminal");
            if (standard.compare(value) == 0) {
                result["Content"]["Code"] = true;
                result["Content"]["Msg"] = "符合预期值";
                json["Content"]["Msg"] = "当前获取值：<span style='color:green'>" + value + "</span><br>测试结果：符合预期值<br>";
            } else {
                result["Content"]["Code"] = false;
                result["Content"]["Msg"] = fmt::format("当前值{0}：与预期值不符", value);
                json["Content"]["Msg"] = "当前获取值：<span style='color:red'>" + (value.empty() ? "未获取到当前值" : value) + "</span><br>测试结果：与预期值不符<br>";
            }
            this->sendMessage(json);
            this->sendMessage(result);
		} else if (msg["Args"].get<std::string>() == "BHDC") {
			std::string value = getBHDC();
			if (standard.compare(value) == 0) {
				result["Content"]["Code"] = true;
				result["Content"]["Msg"] = "符合预期值";
				json["Content"]["Msg"] = "当前获取值：<span style='color:green'>" + value + "</span><br>测试结果：符合预期值<br>";
			} else {
				result["Content"]["Code"] = false;
				result["Content"]["Msg"] = fmt::format("当前值{0}：与预期值不符", value);
				json["Content"]["Msg"] = "当前获取值：<span style='color:red'>" + (value.empty() ? "未获取到当前值" : value) + "</span><br>测试结果：与预期值不符<br>";
			}
			this->sendMessage(json);
			this->sendMessage(result);
		} else if (msg["Args"].get<std::string>() == "SYSTEM-HDSerial"
			   || msg["Args"].get<std::string>() == "SYSTEM-HDSerial_1") {
			this->callInput(msg["Name"].get<std::string>(),
					fmt::format("请手动输入或使用扫码枪扫描{0}：", msg["Name"].get<std::string>()),
					"^([0-9]|[a-z]|[A-Z]|[-]){20}$");
		} else {
			std::string value = this->getValueFromConf(msg["Args"].get<std::string>());
			if (standard.compare(value) == 0) {
				result["Content"]["Code"] = true;
				result["Content"]["Msg"] = "符合预期值";
				json["Content"]["Msg"] = "当前获取值：<span style='color:green'>" + value + "</span><br>测试结果：符合预期值<br>";
			} else {
				result["Content"]["Code"] = false;
				result["Content"]["Msg"] = fmt::format("当前值{0}：与预期值不符", value);
				json["Content"]["Msg"] = "当前获取值：<span style='color:red'>" + (value.empty() ? "未获取到当前值" : value) + "</span><br>测试结果：与预期值不符<br>";
			}
			this->sendMessage(json);
			this->sendMessage(result);
		}
	} catch (std::exception &e) {
		LOG(ERROR) << e.what();
	}
}

void Worker::WSUiRoute(const nlohmann::json &msg)
{
	if (msg["Type"].get<std::string>() == "InputBox"
			&& msg["Id"].get<int>() == this->_CurDialogId) {
		nlohmann::json json = {
			{ "Method", "Messages" }
		};
		nlohmann::json result = {
			{ "Method", "ItemResult" }
		};

		std::string standard = this->_CurItemConf["Standard"].get<std::string>();
		std::string value = recvInput(msg);
		if (standard.compare(value) == 0) {
			result["Content"]["Code"] = true;
			result["Content"]["Msg"] = "符合预期值";
			json["Content"]["Msg"] = "当前获取值：<span style='color:green'>" + value + "</span><br>测试结果：符合预期值<br>";
		} else {
			result["Content"]["Code"] = false;
			result["Content"]["Msg"] = fmt::format("当前值{0}：与预期值不符", value);
			json["Content"]["Msg"] = "当前获取值：<span style='color:red'>" + (value.empty() ? "未获取到当前值" : value) + "</span><br>测试结果：与预期值不符<br>";
		}
		this->sendMessage(json);
		this->sendMessage(result);
	}
}

void Worker::WSSrvRoute(const nlohmann::json &/*msg*/)
{

}



