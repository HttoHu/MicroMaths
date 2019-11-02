#include "pch.h"
#include "HttoTools.h"
String ^ HttoSDK::GetPlatformStrFromStdStr(std::string str)
{
	std::string result = str;
	std::wstring wstr;
	wstr.resize(result.size() + 1);
	size_t charConverted;
	errno_t err = ::mbstowcs_s(&charConverted, (wchar_t *)wstr.data(), wstr.size(), result.data(), result.size());
	wstr.pop_back();
	return ref new String(wstr.c_str());
}
std::string HttoSDK::GetStdStrFromPlatformStr(String ^ pfstr)
{
	using namespace std;
	wstring strr = pfstr->Data();
	std::locale const loc("");
	wchar_t const* from = strr.c_str();
	std::size_t const len = strr.size();
	vector<char>buffer(len + 1);
	std::use_facet<std::ctype<wchar_t>>(loc).narrow(from, from + len, '_', &buffer[0]);
	std::string count = std::string(&buffer[0], &buffer[len]);
	return count;
}
