#pragma once
#ifndef SimpleAlgorithm_H
#define SimpleAlgorithm_H
#include <string>
#include "fraction.h"
namespace Htto
{
	namespace SimpleAlgorithm
	{
		template<typename T>
		T get_min(const T & t1, const T & t2) { if (t1 < t2)return t1;else return t2; }
		int INT_GCD(int n, int m);//获得公因数
		int INT_MAX_FACTOR(int n);//获得最大的平方公因数
		template<typename T>static T ABS(T a) { if (a > T("0")) return a;  else return -a; }//求绝对值
		//T 仅限用于我自己写的类.
		template<typename T>static T Pow(const T&  rhs, int lhs)
		{
			T ret = rhs;
			bool isN = false;
			if (lhs == 0)
				return T("0");
			else if (lhs <= 0)
			{
				isN == true;
				lhs = -lhs;
			}
			for (int i = 1;i < lhs;i++)
			{
				ret = ret*rhs;
				ret.simplification();
			}
			if (isN)
				return (T("1") / ret);
			return ret;
		}//求绝对值
		bool isEqual(int n, float f);
	};

	class StringTools
	{
	public:
		static std::string string_replace(std::string s1, const std::string&s2, const std::string&s3);
		//这个函数是来多项式计算使用,因为后缀计算并不能处理有些情况.比如你输入(x+1)(x-1)他会转换为(x+1)*(x-1). -(x+1)=> -1*(x+1)
		static std::string convert_expression(std::string str);
		static float string_to_float(std::string str);
		static bool isNumber_int(std::string str);
		static bool isNumber(std::string str);
		static int isSingleNumber(char ch);
		static std::string get_rid_of_parentheses(std::string parameter);//去除括号。
		static std::string get_parentheses_model(std::string parameter);
		static std::string get_match_content(std::string parameter, int n = 1);
		static int get_end_index(std::string str, unsigned index);//那个我太懒了，什么tuple算了吧
		static std::string get_number_by_index(std::string str, unsigned index);
	private:
	};
}
#endif
