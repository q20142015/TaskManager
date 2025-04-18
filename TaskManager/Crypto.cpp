#include "Crypto.h"

std::string Crypto::encryptDecrypt(std::string whatToencrypt, std::string key)
{
    int keyIdx = 0;  // текущий индекс байта ключа
    for (int i = 0; i < whatToencrypt.size(); i++) {
        whatToencrypt[i] = whatToencrypt[i] ^ key[keyIdx++]; // шифруем строку и смещаем индекс ключа
        if (keyIdx == key.size())  // если достигли конца ключа - начинаем сначала
            keyIdx = 0;
    }
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
