#include "../polynomial.h"

#include "pch.h"
 
using namespace Htto;
Htto::Polynomial::Polynomial(std::string str)
{
	int state = 0;
	std::string transform;//临时存放string，然后转换为Monomial压入到list中如此反复。
	for (const auto & a : str)
	{
		if (a=='+'||a=='-')
		{
			state = 1;
		}
		switch(state)
		{
		case 0:
			transform += a;
			break;
		case 1:
			if (transform != "")
			{
				push_monomial(transform);
				transform = "";
			}
			transform += a;
			state = 0;
			break;
		default:
			break;
		}
	}
	if (transform != "")
	{
		push_monomial(transform);
		transform = "";
	}
}

void Htto::Polynomial::simplification()const
{
	sort();
	if (data.size() < 2)
	{
		return;
	}
	size_t index1 = 0;
	size_t index2 = 1;
	while (1)
	{
		if (Monomial::is_like_term(data[index1],data[index2]))
		{
			data[index2].coef = data[index1].coef + data[index2].coef;
			data.erase(data.begin()+index1);
			index2--;
			index1 = index2;
		}
		if (index2 == (data.size()-1))
		{
			break;
		}
		index1=index2++;
	}
}

Polynomial Htto::Polynomial::reciprocal() const
{
	Polynomial ret=*this;
	for (auto & a : ret.data)
	{
		a.coef.reciprocal();
		for (auto & b : a.variableTable)
		{
			b.second = -b.second;
		}
	}
	return ret;
}

std::string Htto::Polynomial::ToString()const
{
	if (data.empty())
		return "0";
	else if (data.size() == 1 && data.front().get_coef() == Fraction(0))
		return "0";
	get_rid_of_zero_monomial();
	std::string ret;
	for (size_t i=0;i<data.size();i++)
	{
		if (i != 0)
		{
			if (data[i].coef < Fraction(0))
			{
				ret += "-"+(-data[i]).ToString();
				continue;
			}
			else
				ret += "+";
		}
		ret += data[i].ToString();
	}
	return ret;
}

std::size_t Htto::Polynomial::term_count()const
{
	return data.size();
}

std::size_t Htto::Polynomial::variable_count()const
{
	std::set<std::string> variable_table;
	for (const auto & a : data)
	{
		for (const auto & b : a.variableTable)
		{
			std::set<std::string>::iterator it = variable_table.find(b.first);
			if (it == variable_table.end())
			{
				variable_table.insert(b.first);
			}
		}
	}
	return variable_table.size();
}

Fraction Htto::Polynomial::max_times()const
{
	Fraction thisMax(0);
	for (const auto & a : data)
	{
		if (a.times() > thisMax)
			thisMax = a.times();
	}
	return thisMax;
}

void Htto::Polynomial::sort()const
{
	size_t j, p;
	Monomial tmp;
	for (p = 1;p < data.size();p++)
	{
		tmp = data[p];
		for (j = p;j > 0 && data[j - 1] > tmp;j--)
			data[j] = data[j - 1];

		data[j] = tmp;
	}
}

bool Htto::Polynomial::operator==(Polynomial  poly) const
{
	Polynomial m = *this;
	m.simplification();
	poly.simplification();
	return m.ToString() == poly.ToString();
}

void Htto::Polynomial::get_rid_of_zero_monomial()const
{
	for (size_t i = 0;i < data.size();i++)
	{
		if (data[i].coef == Fraction(0))
		{
			data.erase(data.begin() + i);
			i--;
		}
	}
}

void Htto::Polynomial::push_monomial(const std::string & str)
{
	data.push_back(Monomial(str));
}

Polynomial Htto::Polynomial::operator+(const Polynomial & poly)const
{
	Polynomial ret;
	for (const auto & a : data)
	{
		ret.data.push_back(a);
	}
	for (const auto & a : poly.data)
	{
		ret.data.push_back(a);
	}
	ret.simplification();
	return ret;
}

Polynomial Htto::Polynomial::operator-(const Polynomial & poly)const
{
	Polynomial ret;
	for (const auto & a : data)
	{
		ret.data.push_back(a);
	}

	for (auto a : poly.data)
	{
		a.coef = -a.coef;
		ret.data.push_back(a);
	}
	ret.simplification();
	return ret;
}


Polynomial Htto::Polynomial::operator*(const Polynomial & poly)const
{
	Polynomial ret;
	for (size_t i = 0;i < poly.data.size();i++)
	{
		for (size_t j = 0;j < data.size();j++)
		{
			ret.data.push_back(poly.data[i] * data[j]);
		}
	}
	return ret;
}

Polynomial Htto::Polynomial::operator/(const Polynomial & poly)const
{
	/*

	Polynomial ret;
	if (isSingle() && poly.isSingle())
	{
		if (isSingle())
		{
			for (const auto & a : poly.data)
			{
				ret = ret + Polynomial((data.front() / a).ToString());
			}
		}
		else
		{
			for (const auto & a : data)
			{
				ret = ret + Polynomial((a / ret.data.front()).ToString());
			}
		}
	}
	else
		throw std::runtime_error("Polynomial operator/ :can not count");
	return ret;*/
	return poly.reciprocal()*(*this);
}

Polynomial & Htto::Polynomial::operator+=(const Polynomial & poly)
{
	for (const auto & a : poly.data)
	{
		data.push_back(a);
	}
	simplification();
	return *this;
}

Polynomial & Htto::Polynomial::operator-=(const Polynomial & poly)
{
	for (auto a : poly.data)
	{
		a.coef = -a.coef;
		data.push_back(a);
	}
	simplification();
	return *this ;
}

Polynomial & Htto::Polynomial::operator*=(const Polynomial & poly)
{
	Polynomial ret = *this*poly;
	data = ret.data;
	return *this;
}

Polynomial & Htto::Polynomial::operator/=(const Polynomial &poly)
{
	Polynomial ret = *this / poly;
	data = ret.data;
	return *this;
}

void Htto::Polynomial::remove_term(const Monomial & mono)
{
	using iterator = std::vector<Monomial>::iterator;
	for (size_t i = 0;i < data.size();i++)
	{
		if (data[i] == mono)
		{
			data.erase(data.begin()+i);
		}
	}
}

std::list<std::string> Htto::Polynomial::get_variable_list()const
{
	std::list<std::string> ret;
	for (const auto & a : data)
	{for (const auto & b : a.variableTable)
	{ret.push_back(b.first);}}
	return ret;
}

bool Htto::Polynomial::isNumber() const
{
	if (data.size() == 1)
		if (data.front().variableTable.size() == 0)
			return true;
	return false;
}

Fraction Htto::Polynomial::get_value(const std::map<std::string, Fraction> & vtable)const
{
	Fraction ret;
	for (const auto a : data)
	{
		ret = ret + a.get_value(vtable);
	}
	return ret;
}

Fraction Htto::Polynomial::find(std::string str)
{
	for (const auto & a : data)
	{
		if (a.ID() == str)
		{
			return a.get_coef();
		}
	}
	throw std::runtime_error("Polynomial::<public>find:    no found this term");
}

Polynomial Htto::operator-(Polynomial fra)
{
	for (auto & a : fra.data)
	{
		a = -a;
	}
	return fra;
}
