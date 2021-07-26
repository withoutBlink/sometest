#include "mcrypto.h"

#include <sstream>
#include <algorithm>
#include <string.h>

#include <openssl/md5.h>
#include <openssl/bio.h>
#include <openssl/pem.h>

#include "stdafx.h"

std::string MCrypto::Md5::Encrypt(const std::string &data)
{
    unsigned char buf[16];
    memset(buf, '\0', sizeof(buf));
    MD5(reinterpret_cast<const unsigned char *>(data.c_str()), data.length(), buf);

    std::stringstream dst;
    for (int i = 0; i < static_cast<int>(sizeof(buf)); i++) {
        dst << std::hex << static_cast<int>(buf[i]);
    }

    std::string md5 = dst.str();
    std::transform(md5.begin(), md5.end(), md5.begin(), ::toupper);

    return md5;
}
#if 0
std::string MCrypto::RSA::Encrypt(const std::string &data)
{
    BIO *bio = BIO_new_mem_buf(reinterpret_cast<const void *>(CERT_RSA_PUB), -1);
    if (bio  == nullptr) {
//        LOG(DEBUG) << "BIO_new_mem_buf publicKey error\n";
        return nullptr;
    }

    PEM_read_bio_PUBKEY()
    RSA *publicRsa = PEM_read_bio_RSA_PUBKEY(bio, nullptr, nullptr, nullptr);
    if (publicRsa == nullptr) {
//        LOG(DEBUG) << "PEM_read_bio_RSA_PUBKEY error\n";
        return nullptr;
    }
    BIO_free_all(bio);

    int rsa_len = RSA_size(publicRsa);
    unsigned char *encryptMsg = reinterpret_cast<unsigned char *>(malloc(static_cast<size_t>(rsa_len)));
    memset(encryptMsg, 0, static_cast<size_t>(rsa_len));

    int len = rsa_len - 11;
    if (RSA_public_encrypt(len, reinterpret_cast<const unsigned char *>(data.c_str()), encryptMsg, publicRsa, RSA_PKCS1_PADDING) < 0)
//        LOG(DEBUG) << "RSA_public_encrypt error\n";

    RSA_free(publicRsa);

    BUF_MEM *bptr;

    BIO *b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    BIO *bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);

    BIO_write(b64, encryptMsg, rsa_len);
    BIO_ctrl(b64, BIO_CTRL_FLUSH, 0, nullptr);
    //    BIO_flush(b64);
    BIO_ctrl(b64, BIO_C_GET_BUF_MEM_PTR, 0, reinterpret_cast<char *>(&bptr));
    //    BIO_get_mem_ptr(b64, &bptr);
    BIO_ctrl(b64, BIO_CTRL_SET_CLOSE, BIO_NOCLOSE, nullptr);
    //    BIO_set_close(b64, BIO_NOCLOSE);

    char *buff = reinterpret_cast<char *>(malloc(bptr->length + 1));
    memcpy(buff, bptr->data, bptr->length);
    buff[bptr->length] = 0;
    BIO_free_all(b64);
    free(encryptMsg);

//    LOG(DEBUG) << buff;
    std::string ret = buff;
    free(buff);

    return ret;
}

std::string MCrypto::RSA::Decrypt(const std::string &data)
{
    int length = static_cast<int>(data.length());
    char *buffer = reinterpret_cast<char *>(malloc(static_cast<size_t>(length)));
    memset(buffer, 0, static_cast<size_t>(length));
    BIO *b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

    BIO *bmem = BIO_new_mem_buf(data.c_str(), length);
    bmem = BIO_push(b64, bmem);
    BIO_read(bmem, buffer, length);
    BIO_free_all(bmem);

    BIO *bio = BIO_new_mem_buf(reinterpret_cast<const void *>(CERT_RSA_PRI), -1);
    if (bio == nullptr) {
//        LOG(DEBUG) << "BIO_new_mem_buf privateKey error\n";
        return nullptr;
    }

    OpenSSL_add_all_algorithms();
    RSA *privateRsa = PEM_read_bio_RSAPrivateKey(bio, nullptr, nullptr, nullptr);
    if (privateRsa == nullptr) {
//        LOG(DEBUG) << "PEM_read_RSAPrivateKey error\n";
        return nullptr;
    }
    BIO_free_all(bio);

    int rsa_len = RSA_size(privateRsa);
    unsigned char *decryptMsg = reinterpret_cast<unsigned char *>(malloc(static_cast<size_t>(rsa_len)));
    memset(decryptMsg, 0, static_cast<size_t>(rsa_len));

    int mun = RSA_private_decrypt(rsa_len, reinterpret_cast<const unsigned char *>(buffer), decryptMsg, privateRsa, RSA_PKCS1_PADDING);
    if (mun < 0) {
//        LOG(DEBUG) << "RSA_private_decrypt error\n";
    }
    else
//        LOG(DEBUG) << "RSA_private_decrypt " << decryptMsg;

    RSA_free(privateRsa);

    free(buffer);

    std::string ret = reinterpret_cast<char *>(decryptMsg);
    free(decryptMsg);

    return ret;
}
#endif
