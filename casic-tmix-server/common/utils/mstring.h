/*
* @Author:	徐哲阳
* @EMail:	xuzheyangchn@foxmail.com
* @FileName:	mstring.h
* @Created:	2020-03-09 06:55:08
* @Description: 补充 std::string
*/

#ifndef MSTRING_H
#define MSTRING_H

#include <vector>
#include <string>

namespace MString {
    std::vector<std::string> SplitString(const std::string& str, const std::string& ch);
    bool StartsWith(const std::string& str, const std::string& start);
    bool EndsWith(const std::string& str, const std::string& end);
    void Replace(std::string &str, const std::string &src, const std::string &dst);
    void Trim(std::string &str, char ch);
}

#endif // MSTRING_H
