#include "../equation.h"

#include "pch.h"
 
using namespace Htto::Count;
using namespace Htto;
//快速查找,EX00+ Equation后面的序号即可跳转到此类的方法定义.
//===========================EX001 ====================================
std::vector<Fraction> Htto::Count::Equation::solve(const std::string & str)
{
	Polynomial poly_temp = get_polynomial(str);
	poly_temp.simplification();
	if (poly_temp.max_times() > Htto::Fraction(2))
		throw std::runtime_error("Equation::solve:   can not solve the equation that the times over 2");
	else if (poly_temp.variable_count() != 1)
		throw std::runtime_error("Equation::solve:   please input a single variable equation");
	if (poly_temp.max_times() == Fraction(1))
	{
		const size_t size = poly_temp.term_count();
		std::vector<Fraction> vec(2);
		for (int i = 0;i < size;i++)
		{
			vec[poly_temp[i].times()] = poly_temp[i].get_coef();
		}
		if (size == 1)
			return{ Fraction(0) };
		else if (size == 2)
		{
			return{ (-vec[0]/vec[1]) };
		}
	}
	if (poly_temp.max_times() == Fraction(2))
	{
		const size_t size = poly_temp.term_count();
		std::vector<Fraction> vec(3);
		for (int i = 0;i < size;i++)
		{
			vec[poly_temp[i].times()] = poly_temp[i].get_coef();
		}
		Fraction diat = (vec[1] * vec[1]) - (Fraction(4)*vec[0] * vec[2]);
		if (diat < Fraction(0))
			return{};
		else
		{
			diat.numsqrt();
			return{ ((-vec[1] - diat) / (Fraction(2)*vec[2])),((-vec[1] + diat) / (Fraction(2)*vec[2])) };
		}
	}
}
Polynomial Htto::Count::Equation::get_polynomial(const std::string & str)
{
	if (str.find('=') == std::string::npos)
	{
		throw std::runtime_error("Equation::<public>get_polynomial: '=' disappeared.");
	}
	size_t index = str.find('=');
	std::string left = str.substr(0, index);
	std::string right = str.substr(index + 1, str.size() - index - 1);
	return merage(left, right);
}
Htto::Polynomial Htto::Count::Equation::merage(const std::string & left, const std::string & right)
{
	UniversalCount<Polynomial>temp;
	temp.InfixToPostfix(Htto::Count::SimpleCount::PushToListP(StringTools::convert_expression(left)));
	Polynomial poly_left = temp.Count();
	temp.InfixToPostfix(Htto::Count::SimpleCount::PushToListP(StringTools::convert_expression(right)));
	Polynomial poly_right = temp.Count();
	return (poly_left - poly_right);
}
//===========================EX002 ====================================
std::map<std::string, Fraction> Htto::Count::Equation2::solve(const std::vector<std::string>& vec)
{
	bool can_be_solved = true;;
	using iterator = std::map<std::string, Htto::Polynomial>::iterator;
	std::vector<Polynomial> vec_poly(vec.size());
	std::map<std::string, Htto::Polynomial> trans_table;//肖元表
	std::map<std::string, Fraction> result;
	Polynomial temp;
	std::string str_temp;
	for (auto a : vec)
	{
		for (iterator it = trans_table.begin();it != trans_table.end();it++)
		{
			a = Htto::StringTools::string_replace(a, it->first, "("+it->second.ToString()+")");
		}
		temp = get_polynomial(a);
		temp.simplification();
		temp.get_rid_of_zero_monomial();
		std::string str = temp.get_variable_list().front();
		if (temp.variable_count() == 1)
		{
			can_be_solved = true;
			Fraction fra = Equation::solve(temp.ToString()+"=0").front();
			result.insert({ str,fra});
			trans_table.insert({ str,Polynomial(fra.ToString())});
			continue;
		}
		trans_table.insert({ str,convert_single_to_polynomial(str,temp) });
	}
	if (can_be_solved == false)
		throw std::runtime_error("sorry I can not solve the equation.");
	for (iterator it=trans_table.begin();it!=trans_table.end();it++)
	{
		if (!it->second.isNumber())
		{
			Fraction tp = solve_driver(it->first, trans_table);
			result.insert({ it->first, tp });
			it->second = Polynomial(tp.ToString());
		}
	}
	return result;
}
Polynomial Htto::Count::Equation2::convert_single_to_polynomial(const std::string & vname, const Polynomial & poly)
{
	Polynomial ret = poly;
	Fraction coef=ret.find(vname);
	ret.remove_term(Monomial(vname));
	ret = -ret;
	ret = ret / Polynomial(coef.ToString());
	ret.simplification();
	return ret;
}
Fraction Htto::Count::Equation2::solve_driver(std::string v, const std::map<std::string, Polynomial> &table)
{
	if (table.find(v) == table.end())
		throw std::runtime_error("Equation2::<private>solve_driver: can not find specific variable");
	std::map<std::string, Polynomial>::const_iterator it = table.find(v);
	if (it->second.isNumber() == true)
		return Fraction(it->second.ToString());
	std::map<std::string, Fraction> valueTable;
	std::list<std::string> name_table=it->second.get_variable_list();
	for (const auto & a : name_table)
	{
		valueTable.insert({ a,solve_driver(a,table) });
	}
	return it->second.get_value(valueTable);
}
//===========================EX003 ====================================
std::vector<Fraction> Htto::Count::Equation3::solve(const std::string & str)
{
	Rational_fraction tp_rational_fraction = get_rational_fraction(str);
	tp_rational_fraction.simplification();
	if (tp_rational_fraction.denmonilator() == Rational_fraction("1"))
		return Equation::solve(tp_rational_fraction.molecular().ToString());
	else if(tp_rational_fraction.denmonilator() == Rational_fraction("-1"))
		return Equation::solve((-tp_rational_fraction).molecular().ToString());
	std::set<Fraction> false_root;
	std::vector<Fraction> vec_froot = Equation::solve(tp_rational_fraction.denmonilator().ToString());
	for (const auto & a : vec_froot)
		false_root.insert(a);
	std::vector<Fraction> roots= Equation::solve(tp_rational_fraction.molecular().ToString());
	std::vector<Fraction>ret;
	for (const auto & a : roots)
	{
		if (false_root.find(a) == false_root.end())
		{
			ret.push_back(a);
		}
	}
	return ret;
}
Rational_fraction Htto::Count::Equation3::get_rational_fraction(const std::string & str)
{
	if (str.find('=') == std::string::npos)
	{
		throw std::runtime_error("Equation::<public>get_polynomial: '=' disappeared.");
	}
	size_t index = str.find('=');
	std::string left = str.substr(0, index);
	std::string right = str.substr(index + 1, str.size() - index - 1);
	return merage(left, right);
}
Rational_fraction Htto::Count::Equation3::merage(const std::string & left, const std::string & right)
{
	UniversalCount<Rational_fraction>temp;
	temp.InfixToPostfix(Htto::Count::SimpleCount::PushToListR(StringTools::convert_expression(left)));
	Rational_fraction poly_left = temp.Count();
	temp.InfixToPostfix(Htto::Count::SimpleCount::PushToListR(StringTools::convert_expression(right)));
	Rational_fraction poly_right = temp.Count();
	return (poly_left - poly_right);
}
