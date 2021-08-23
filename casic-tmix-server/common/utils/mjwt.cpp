#include "mjwt.h"

#include "stdafx.h"
#include "jwt/jwt.hpp"
#include "easylogging++.h"

#include "json.hpp"

std::string mjwt::signature(const std::string &username)
{
    std::string token;

    do {
        try {
            jwt::jwt_object obj{jwt::params::algorithm("HS256"), jwt::params::secret(JWT_PRIVATE_KEY), jwt::params::payload({{"username", username}})};

            auto nowtime = std::chrono::system_clock::now();
            obj.add_claim("iat", nowtime);
            obj.add_claim("exp", nowtime + std::chrono::seconds{JWT_EXPIRED});
            token = obj.signature();
        } catch (std::exception &e) {
            LOG(ERROR) << e.what();
        }
    } while (false);

    return token;
}

//std::string mjwt::decode(const std::string &token)
//{
//    auto dec_obj = jwt::decode(token, jwt::params::algorithms({"HS256"}), jwt::params::secret(JWT_PRIVATE_KEY), jwt::params::verify(true));
//    auto payload = dec_obj.payload();
////    get_claim_value("");

////    try {
////      } catch (const jwt::TokenExpiredError& e) {
////        //Handle Token expired exception here
////        //...
////      } catch (const jwt::SignatureFormatError& e) {
////        //Handle invalid signature format error
////        //...
////      } catch (const jwt::DecodeError& e) {
////        //Handle all kinds of other decode errors
////        //...
////      } catch (const jwt::VerificationError& e) {
////        // Handle the base verification error.
////        //NOTE: There are other derived types of verification errors
////        // which will be discussed in next topic.
////      } catch (...) {
////        std::cerr << "Caught unknown exception\n";
////      }
//}

std::string mjwt::expressjwt(const std::string &token)
{
//    auto payload = dec_obj.payload();

    std::string username;
    try {
        auto dec_obj = jwt::decode(token, jwt::params::algorithms({"HS256"}), jwt::params::secret(JWT_PRIVATE_KEY), jwt::params::verify(true));
        LOG(INFO) << dec_obj.payload();
        nlohmann::json json = dec_obj.payload().create_json_obj();
        username = json["username"].get<std::string>();
    } catch (const jwt::TokenExpiredError& e) {
        LOG(ERROR) << "Handle Token expired exception here";
    } catch (const jwt::SignatureFormatError& e) {
        LOG(ERROR) << "Handle invalid signature format error";
    } catch (const jwt::DecodeError& e) {
        LOG(ERROR) << "Handle all kinds of other decode errors";
    } catch (const jwt::VerificationError& e) {
        LOG(ERROR) << "Handle the base verification error";
    } catch (...) {
        LOG(ERROR) << "Caught unknown exception\n";
    }

    return username;
}
