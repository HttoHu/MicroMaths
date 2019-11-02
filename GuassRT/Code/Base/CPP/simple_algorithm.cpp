//基本数值处理和字符处理
#include "../simple_algorithm.h"
#include <iostream>
#include <cctype>

#include "pch.h"
 
//获得最大公因数
using namespace Htto;
int Htto::SimpleAlgorithm::INT_GCD(int n, int m)
{
	if (n < m)
	{
		int temp;
		temp = n;
		n = m;
		m = temp;
	}
	if (m == 0)
		return 1;
	while (n%m)
	{
		int r = n%m;
		n = m;
		m = r;
	}
	return m;
}
//获得最大因子(未优化)
int Htto::SimpleAlgorithm::INT_MAX_FACTOR(int n)
{
	if (n < 1)
		return 1;
	for (int i = n - 1;i > 0;i--)
	{
		if (!(n%i))
			return i;
	}
	return 1;
}
bool Htto::SimpleAlgorithm::isEqual(int n, float f)
{
	if ((float)n == f)
		return true;
	else
		return false;
}
//====================== TAB AA4  (class) StringTools=========================
int Htto::StringTools::isSingleNumber(char ch)
{
	if (ch >= 48 && ch <= 57)
		return 1;
	else if (ch == '.')
		return -1;
	else
		return 0;
}

int STgetCharValue(char ch)
{
	if (ch == '(')
		return 1;
	else if (ch == ')')
		return -1;
	else if (ch == '[')
		return 2;
	else if (ch == ']')
		return -2;
	else
		return 0;
}
bool Htto::StringTools::isNumber_int(std::string str)
{
	for (size_t i = 0;i < str.size();i++)
	{
		if (str[i] >= 48 && str[i] <= 57)
			continue;
		else
			return false;
	}
	return true;
}
bool Htto::StringTools::isNumber(std::string str)
{
	for (size_t i = 0;i < str.size();i++)
	{
		if ((str[i] >= 48 && str[i] <= 57) || str[i] == '.')
			continue;
		else
			return false;
	}
	int count = 0;
	for (auto a : str)
	{
		if (a == '.')
			count++;
	}
	if (count > 1)
		return false;
	return true;
}
std::string Htto::StringTools::get_rid_of_parentheses(std::string parameter)
{
	std::string ret;
	int state = 0;
	unsigned index = 0;
	for (;index < parameter.size();index++)
	{
		state += STgetCharValue(parameter[index]);
		if (state == 0 && parameter[index] != ')')
		{
			ret += parameter[index];
		}
		else
		{
			continue;
		}
	}
	return ret;
}
std::string Htto::StringTools::get_parentheses_model(std::string parameter)
{
	std::string ret;
	unsigned index = 0;
	int nindex = 0;
	int lastState = 0;
	int state = 0;
	for (;index < parameter.size();index++)
	{
		lastState = state;
		state += STgetCharValue(parameter[index]);
		if (lastState - state == 0)
		{
			if (state < lastState)
				++nindex;
		}
		else
		{
			ret += parameter[index];
			continue;
		}
	}
	return ret;
}

std::string Htto::StringTools::get_match_content(std::string parameter, int n)
{
	std::string rv;
	int state = 0;
	int lastState = 0;
	unsigned index = 0;
	int nindex = 1;
	for (;index < parameter.size();index++)
	{
		lastState = state;
		state += STgetCharValue(parameter[index]);

		if (lastState != state&&lastState > state&&lastState < 2)
		{
			if (nindex++ == n)
			{
				break;
			}
		}
		else if (lastState != 0)
		{
			if (nindex == n)
				rv += parameter[index];
		}
	}
	return rv;
}

int Htto::StringTools::get_end_index(std::string str, unsigned index)
{
	if (index >= str.size())
		throw std::out_of_range("stringTools.cpp->get_number_end_index: index too large");
	int endPos = index;
	while (isSingleNumber(str[endPos]))
	{
		if (endPos != str.size())
			++endPos;
		else
			break;
	}
	return endPos;
}

std::string Htto::StringTools::get_number_by_index(std::string str, unsigned index)
{
	if (index >= str.size())
		throw std::out_of_range("stringTools.cpp->get_number_end_index: hhindex toa large");
	int endPos = index;
	while (isSingleNumber(str[endPos]))
	{
		if (endPos != str.size())
			++endPos;
		else
			break;
	}
	return str.substr(index, endPos);
}

std::string Htto::StringTools::string_replace(std::string  s1, const std::string & s2, const std::string & s3)
{
	using std::string;
	string::size_type pos = 0;
	string::size_type a = s2.size();
	string::size_type b = s3.size();
	while ((pos = s1.find(s2, pos)) != string::npos)
	{
		s1.erase(pos, a);
		s1.insert(pos, s3);
		pos += b;
	}
	return s1;
}

std::string Htto::StringTools::convert_expression(std::string str)
{
	int index = 0;
	int state = 0;
	int old_state = 0;
	/*
	for (const auto & a : str)
	{
	old_state = state;
	if (isdigit(a) || isalpha(a))
	state = 1;
	else if (a == '+' || a == '-')
	state = 2;
	else if (a == '(')
	{
	state = 3;
	}
	else if (a == ')')
	state = 4;
	else
	state = 0;
	switch (state)
	{
	case 1:
	if (old_state == 4)
	{
	str.insert(index, "*");
	index+=1;
	}
	break;
	case 3:
	if (old_state == 2 && index == 1)
	{
	str.insert(index, "1*");
	index += 2;
	}
	else if (old_state == 1 || old_state == 4)
	{
	str.insert(index, "*");
	index += 1;
	}
	break;
	default:
	break;
	}
	index++;
	}
	*/
	for (size_t i = 0;i < str.size();i++)
	{
		char & a = str[i];
		old_state = state;
		if (isdigit(a) || isalpha(a))
			state = 1;
		else if (a == '+' || a == '-')
			state = 2;
		else if (a == '(')
		{
			state = 3;
		}
		else if (a == ')')
		{
			state = 4;
		}
		else
			state = 0;
		//(1/3)z-(3/4)y-3
		//std::cout << "S" + state << "\nOLD" << old_state << std::endl;
		switch (state)
		{
		case 1:
			if (old_state == 4)
			{
				str.insert(i, "*");
			}
			break;
		case 3:
			if (old_state == 2 /*&& index == 1*/)
			{
				str.insert(i, "1*");
			}
			else if (old_state == 1 || old_state == 4)
			{
				str.insert(i, "*");
			}
			break;
		default:
			break;
		}
	}
	return str;
}

float Htto::StringTools::string_to_float(std::string str)
{
	bool isN = ((str[0] == '-') || (str[0] == '+'));
	int frontPart = 0;
	int tv = 1;
	int index = 0;
	if (isN)
	{
		index++;
	}

	for (const auto & a : str)
	{
		if (std::isdigit(a) || a == '.' || a == '-' || a == '+')
			continue;
		else
			throw std::runtime_error("error input" + str + " string_to_float is a bad input");
	}
	while (index != str.size() && str[index] != '.')
	{
		frontPart = frontPart * 10 + (str[index] - 48);
		index++;
	}
	if (index == str.size())
	{
		if (isN&&str[0] == '-')
			return -(float)frontPart;
		return (float)frontPart;
	}
	index++;
	float ret = (float)frontPart;
	tv = 1;
	while (index != str.size())
	{
		tv *= 10;
		ret += (float)(str[index++] - 48) / (float)tv;
	}
	if (isN&&str[0] == '-')
		return -ret;
	return ret;
}

