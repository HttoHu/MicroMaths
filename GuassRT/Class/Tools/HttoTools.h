#pragma once
#include <string>
#define UWPSDK
#ifdef UWPSDK
//UWP SDK
using namespace Platform;
namespace HttoSDK
{
	//°æ±¾2017 1.0°æ±¾
	String^GetPlatformStrFromStdStr(std::string str);
	std::string GetStdStrFromPlatformStr(String^ pfstr);
}
#endif