#include "Crypto.h"

std::string Crypto::encryptDecrypt(std::string whatToencrypt, std::string key)
{
    int keyIdx = 0;  // ������� ������ ����� �����
    for (int i = 0; i < whatToencrypt.size(); i++) {
        whatToencrypt[i] = whatToencrypt[i] ^ key[keyIdx++]; // ������� ������ � ������� ������ �����
        if (keyIdx == key.size())  // ���� �������� ����� ����� - �������� �������
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
