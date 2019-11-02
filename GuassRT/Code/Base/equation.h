#pragma once
#include "Count.h"
#include <vector>
namespace Htto
{
	namespace Count
	{
		//简单方程
		class Equation
		{
		public:
			//简单方程仅限单元变量x 一次方程和二次方程
			static std::vector<Fraction> solve(const std::string & str);
			static Polynomial get_polynomial(const std::string & str);
			static Polynomial merage(const std::string & left, const std::string & right);
		private:
		};
		//分式方程,兼容简单方程.
		class Equation3 :Equation
		{
		public:
			static std::vector<Fraction> solve(const std::string & str);
			static Rational_fraction get_rational_fraction(const std::string & str);
			static Rational_fraction merage(const std::string & left, const std::string & right);
		};
		//多元方程1次方程
		class Equation2:Equation
		{
		public:
			static std::map<std::string, Fraction>solve(const std::vector<std::string>& vec);
	//	protected:
			static Polynomial convert_single_to_polynomial(const std::string & vname, const Polynomial & poly);
		public:
			static Fraction solve_driver(std::string v, const std::map<std::string, Polynomial>& table);
		};
	}
}