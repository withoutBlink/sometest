#ifndef FILEOPT_H
#define FILEOPT_H

#include <string>

namespace FileOpt {
std::string ReadFile(const std::string& file);
bool WirteFile(const std::string& file, const std::string data);
}

#endif // FILEOPT_H
