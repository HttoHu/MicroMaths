/*单项式类
版本:1.01
日期:17-5-17
*/
#pragma once
#include <string>
#include <cctype>
#include <list>
#include "fraction.h"
#include <map>
namespace Htto
{
	namespace Count
	{
		class factorization;
	}
	class Polynomial;
	class Monomial
	{
	private:
		friend class Polynomial;
		friend class Count::factorization;
		friend Polynomial operator-(Polynomial  fra);
		friend Monomial operator-(Monomial  fra);
		Fraction coef;//系数
		std::map<std::string, Fraction> variableTable;
	public:
		Monomial() = default;
		Monomial(std::string str);
		Monomial(const Monomial& M) :variableTable(M.variableTable), coef(M.coef) {}
		Monomial(Monomial && m)noexcept { coef = m.coef;variableTable = m.variableTable; }
		Monomial & operator=(const Monomial & M)
		{
			variableTable = M.variableTable;
			coef = M.coef;
			return *this;//伟大的Sccot Meray(模糊记忆~） 教导我们 copying or copying-assigned operator要返回一个引用.
		}
		bool operator!=(const Monomial & M)const;
		Monomial operator* (const Monomial &M)const;
		Monomial operator/ (const Monomial & M)const;
		bool operator==(const Monomial & M)const;
		bool operator < (const Monomial & M)const;
		bool operator >(const Monomial & M)const;
		std::string ToString()const;
		bool is_square()const;
		//the difference between name and ID:
		//name return times,but ID not
		std::string name()const;
		std::string ID()const;
		static bool is_like_term(const Monomial &, const Monomial &);//判断是否是同类项
		void simplifiction();
		Monomial get_numsqrt()const;
		Fraction get_coef()const
		{
			return coef;
		}
		Fraction get_value(const std::map<std::string, Fraction> & vtable)const;
		Fraction times()const;
	};
}