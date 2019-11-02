#include "../factorization.h"

#include "pch.h"
 
using namespace Htto;
std::vector<Polynomial> Htto::Count::factorization::factoring(Polynomial poly)
{
	std::vector<Polynomial> ret;
	poly.simplification();
	Monomial m_factor = poly.data.at(0);//cheak index.
	/*if (poly.term_count() == 1)
	{
		for (auto & a : poly.data)
		{
			for (auto & b : a.variableTable)
			{
				int times = a.times();
				for (size_t t = times;t > 0;t--)
				{
					ret.push_back(Polynomial(b.first));
					b.second = b.second-Fraction("1");
				}
			}
		}
	}*/
	for (const auto & a : poly.data)
	{
		m_factor = get_public_factor(m_factor, a);
	}
	if(m_factor!=Monomial("1"))
		ret.push_back(Polynomial({ m_factor }));
	poly /= Polynomial({ m_factor });
	if (poly.term_count() == 3)
	{
		std::sort(poly.data.begin(), poly.data.end(), [](const Monomial & m1, const Monomial & m2) 
		{
			if (m1.times() > m2.times())
				return true;
			else if (m1.times() == m2.times()&&m1.get_coef() > m2.get_coef())
				return true; 
			else return false;
		});
		if (true)
		{
			bool isN=false;
			std::vector<Monomial> vec;
			for (const auto & a : poly.data)
			{
				if (a.is_square())
				{
					vec.push_back(a);
				}
				else
				{
					if (a < Monomial("0"))
						isN = true;
				}
			}
			if (vec.size() >= 2)
			{
				Monomial m3("1");
				for (const auto & a : vec)
				{
					m3 = m3*a.get_numsqrt();
				}
				m3 = m3*Monomial("2");
				if (std::find_if(poly.data.cbegin(), poly.data.cend(), [m3](const Monomial &M) {if (m3==M&&m3.get_coef() == M.get_coef())return true; else return false;}) != poly.data.cend())
				{
					Polynomial p1({ vec[0].get_numsqrt(),vec[1].get_numsqrt() });
					if (isN)
						p1.data[1] = -p1.data[1];
					std::vector<Polynomial> n_vec = factoring(p1);
					if (n_vec.size() == 1)
					{
						ret.push_back(p1);
						ret.push_back(p1);
					}
					else
						for (const auto & a : n_vec)
						{
							ret.push_back(a);
							ret.push_back(a);
						}
					poly = Polynomial("");
				}
			}
		}
	}
	else
	{
		if (poly.term_count() == 2)
		{			//std::cout << poly.data[0].ToString() << std::endl;
			//std::cout << poly.data[1].ToString() << std::endl;
			std::sort(poly.data.begin(), poly.data.end(), [](const Monomial & m1, const Monomial & m2) {return m1.get_coef() > m2.get_coef();});
			if (poly.data[1].coef < Fraction(0) && poly.data[0].is_square() && (-poly.data[1]).is_square()&& (int)poly.data[0].coef > 0)
			{
				Polynomial p1({ poly.data[0].get_numsqrt(),(-poly.data[1]).get_numsqrt() });
				Polynomial p2({ poly.data[0].get_numsqrt(),-(-poly.data[1]).get_numsqrt() });
				std::vector<Polynomial> n_vec = factoring(p1);
				std::vector<Polynomial> m_vec = factoring(p2);
				for (const auto & a : n_vec)
					ret.push_back(a);
				for (const auto & b : m_vec)
					ret.push_back(b);
				poly = Polynomial("1");
			}
		}
	}
	if(poly!=Polynomial("0"))
		ret.push_back(poly);
	get_rid_of_terms(ret);
	return ret;
}
Monomial Htto::Count::factorization::get_public_factor(const Monomial & m1, const Monomial & m2)
{
	using const_iterator = std::map<std::string, Fraction>::const_iterator;
	Monomial ret("1");
	if (m1.coef.is_interger() && m2.coef.is_interger())
	{
		ret.coef = Fraction(Htto::SimpleAlgorithm::INT_GCD(m1.coef, m2.coef));
		
	}
	for (const_iterator it = m1.variableTable.cbegin(); it != m1.variableTable.cend();it++)
	{
		const_iterator it2 = m2.variableTable.find(it->first);
		if (it2 != m2.variableTable.end())
		{
			ret.variableTable.insert({ it->first ,Htto::SimpleAlgorithm::get_min(it->second,it2->second) });
		}
	}
	return ret;
}
void Htto::Count::factorization::get_rid_of_terms(std::vector<Polynomial>& vec)
{
	bool isN = false;
	for (size_t i = 0;i < vec.size();i++)
	{
		if (vec[i] == Polynomial("1"))
		{
			vec.erase(vec.begin() + i);
			i--;
			continue;
		}
		if (vec[i] == Polynomial("-1"))
		{
			vec.erase(vec.begin() + i);
			i--;
			isN = !isN;
			continue;
		}
		if (isN)
		{
			vec.push_back(Polynomial("-1"));
			auto tmp = vec.begin();
			vec.end() = vec.begin();
			vec.begin() = tmp;
		}
	}
}
