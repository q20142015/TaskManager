#pragma once
#pragma comment(lib, "rpcrt4.lib") 
#include <windows.h>
#include <vector>
#include <rpcdce.h>
#include <string>
#include <numeric>

public class Crypto
{
public:
	static	std::string encryptDecrypt(std::string whatToencrypt, std::string key);
	static	std::string getUid();
	static	std::string getData();
};
