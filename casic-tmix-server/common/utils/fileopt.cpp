#include "fileopt.h"

#include "fstream"

std::string FileOpt::ReadFile(const std::string &file)
{
    std::ifstream fin(file);
    std::string str((std::istreambuf_iterator<char>(fin)),
                    std::istreambuf_iterator<char>());
    return str;
}

bool FileOpt::WirteFile(const std::string &file, const std::string data)
{
    int ret = false;
    do {
        std::ofstream out;
        out.open(file, std::ios::trunc);
        if (!out.is_open())
            break;

        out << data;
        out.close();

        ret = true;
    } while (false);

    return ret;
}

