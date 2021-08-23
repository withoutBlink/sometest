#ifndef MCRYPTO_H
#define MCRYPTO_H

#include <string>

namespace MCrypto {
namespace Md5 {
    std::string Encrypt(const std::string &data);
}

//namespace RSA {
//    std::string Encrypt(const std::string &data);
//    std::string Decrypt(const std::string &data);
//}
}

#endif // MCRYPTO_H
