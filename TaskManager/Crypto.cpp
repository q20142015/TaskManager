#include "Crypto.h"

std::string Crypto::encryptDecrypt(std::string whatToencrypt, std::string key)
{
   std::vector<char> resStr;
    int i = 0;
    for(char& c : whatToencrypt)
    {
        resStr.push_back((char)(c ^ key[i++]));
        i = i % key.size();
    }
    whatToencrypt = accumulate(resStr.cbegin(), resStr.cend(), std::string{});
    return whatToencrypt;
}
std::string Crypto::getUid()
{
        UUID uuid;
        RPC_CSTR  uuid_str;
        std::string uuid_out;

        UuidCreate(&uuid);
        UuidToStringA(&uuid, &uuid_str);

        uuid_out = (char*)uuid_str;
        RpcStringFreeA(&uuid_str);
        return uuid_out;
}
std::string Crypto::getData()
{
    return " ";
}
