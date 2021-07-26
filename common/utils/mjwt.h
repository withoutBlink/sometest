#ifndef MJWT_H
#define MJWT_H

#include <string>

#include "jwt/jwt.hpp"

namespace mjwt {

std::string signature(const std::string& username);
std::string expressjwt(const std::string& token);

}

#endif // MJWT_H
