#pragma once
#include <string>
#define UWPSDK
#ifdef UWPSDK
//UWP SDK
using namespace Platform;
namespace HttoSDK
{
	//�汾2017 1.0�汾
	String^GetPlatformStrFromStdStr(std::string str);
	std::string GetStdStrFromPlatformStr(String^ pfstr);
}
#endif