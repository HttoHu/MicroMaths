#pragma once
#include "Code\Base\equation.h"
#include "Code\merdog\include\environment.hpp"
#include "Class\Tools\HttoTools.h"
#include <collection.h>
namespace GuassRT
{
	public ref class Equation sealed
	{
	public:
		static String^ Solve(String^ str)
		{
			std::string expr = HttoSDK::GetStdStrFromPlatformStr(str);
			try
			{
				std::vector<Htto::Fraction> vec = Htto::Count::Equation::solve(expr);
				String^ ret;
				if (vec.size() == 1)
					ret += HttoSDK::GetPlatformStrFromStdStr(vec[0].ToString());
				else
					ret += HttoSDK::GetPlatformStrFromStdStr(vec[0].ToString() + "\t\t" + vec[1].ToString());
				return ret;
			}
			catch (...)
			{
				return "BOOM!";
			}
		}
		static String^ SolveInequation(String^ str)
		{

			std::string expr = HttoSDK::GetStdStrFromPlatformStr(str);
			try
			{
				std::vector<Htto::Fraction> vec = Htto::Count::Equation::solve(expr);
				String^ ret;
				if (vec.size() == 1)
					ret += HttoSDK::GetPlatformStrFromStdStr(vec[0].ToString());
				else
					ret += HttoSDK::GetPlatformStrFromStdStr(vec[0].ToString() + "\t\t" + vec[1].ToString());
				return ret;
			}
			catch (...)
			{
				return "BOOM!";
			}
		}
		static String^ SolveMoreQuantityVariable(const Array<String^>^ exprs)
		{
			std::vector<std::string> vecExprs;
			for (const auto & a : exprs)
			{
				vecExprs.push_back(HttoSDK::GetStdStrFromPlatformStr(a));
			}
			try
			{
				String^ ret;
				std::map<std::string, Htto::Fraction> table = Htto::Count::Equation2::solve(vecExprs);
				int length = table.size();
				int index = 0;
				for (const auto & a : table)
				{
					ret += HttoSDK::GetPlatformStrFromStdStr(a.first) + "=" + HttoSDK::GetPlatformStrFromStdStr(a.second.ToString()) + "\n";
				}
				return ret;
			}
			catch (...)
			{
				Platform::Collections::Map<String^, String^>^ ret = ref new Platform::Collections::Map<String^, String^>();
				String^ str = "";
				for (const auto & a : exprs)
				{
					str += "<" + a + ">";
				}
				return str;
			}
		}
		static String^ Calculate(String ^ str)
		{
			std::string expr = HttoSDK::GetStdStrFromPlatformStr(str);
			try
			{
				std::string ret = Htto::Count::SimpleCount::Rational_fraction_count(expr).ToString();
				return HttoSDK::GetPlatformStrFromStdStr(ret);
			}
			catch (...)
			{
				return "BOOM!";
			}
		}
		static String^ Merdog(String^ Str)
		{
			std::string result;
			std::string content;
			try
			{
				content = HttoSDK::GetStdStrFromPlatformStr(Str);
				result = Mer::run_interpreter(content);
			}
			catch (...)
			{ 
				return "BOOM!";
			}
			return HttoSDK::GetPlatformStrFromStdStr(result);//Mer::run_interpreter(content));
		}
	};
}