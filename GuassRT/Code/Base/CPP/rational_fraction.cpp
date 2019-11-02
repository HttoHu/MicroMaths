#include "../rational_fraction.h"

#include "pch.h"
 
using namespace Htto;

std::string Htto::Rational_fraction::ToString()const
{
	if (m_denomilator.ToString() == "1")
		return m_molecular.ToString();
	return "(" + m_molecular.ToString() + std::string(")/(") + m_denomilator.ToString() + ")";
}

Rational_fraction Htto::Rational_fraction::get_reciprocal() const
{
	Rational_fraction ret = *this;
	std::swap(ret.m_denomilator, ret.m_molecular);
	if (ret.m_denomilator == Polynomial("0"))
		throw std::runtime_error("Rational_fraction::<public>get_reciprocal() m_denmilar is zero");
	return ret;
}

Rational_fraction Htto::Rational_fraction::operator+(const Rational_fraction & r_fraction)const
{
	Polynomial den = m_denomilator*(r_fraction.m_denomilator);
	Rational_fraction ret;
	ret.m_denomilator = den;
	ret.m_molecular = (m_molecular*r_fraction.m_denomilator) + (r_fraction.m_molecular*m_denomilator);
	ret.simplification();
	return ret;
}
Rational_fraction Htto::Rational_fraction::operator-(const Rational_fraction &r_fraction) const
{
	Polynomial den = m_denomilator*r_fraction.m_denomilator;
	Rational_fraction ret;
	ret.m_denomilator = den;
	ret.m_molecular = (m_molecular*r_fraction.m_denomilator) - (r_fraction.m_molecular*m_denomilator);
	ret.simplification();
	return ret;
}
Rational_fraction Htto::Rational_fraction::operator*(const Rational_fraction & r_fraction) const
{
	Rational_fraction ret=*this;
	ret.m_denomilator = ret.m_denomilator*r_fraction.m_denomilator;
	ret.m_molecular = ret.m_molecular*r_fraction.m_molecular;
	ret.simplification();
	return ret;
}
Rational_fraction Htto::Rational_fraction::operator/(const Rational_fraction & r_fraction) const
{
	if (*this == r_fraction)
	{
		return Polynomial("1");
	}
	Rational_fraction ret = (*this)*(r_fraction.get_reciprocal());
	return ret;
}
bool Htto::Rational_fraction::operator==(const Rational_fraction &rf) const
{
	if (m_molecular*rf.m_denomilator == m_denomilator*rf.m_molecular)
		return true;
	else
		return false;
}
void Htto::Rational_fraction::simplification()
{
	Monomial d_public_factor=m_denomilator.data.front();
	Monomial m_public_factor = m_molecular.data.front();;
	for (const auto & a : m_denomilator.data)
		d_public_factor = Count::factorization::get_public_factor(d_public_factor, a);
	for (const auto & a : m_molecular.data)
		m_public_factor = Count::factorization::get_public_factor(m_public_factor, a);
	Monomial last=Count::factorization::get_public_factor(d_public_factor,m_public_factor);
	m_denomilator /= Polynomial({ last });
	m_molecular /= Polynomial({ last });
	m_denomilator.simplification();
	m_molecular.simplification();
}
#ifdef CONSOLE_DEBUG

void Htto::Rational_fraction::debug()
{
	std::cout << "rational_fraction debug msg:\n";
	std::cout << m_molecular.ToString()<<std::endl;
	std::cout << m_denomilator.ToString() << std::endl;
}
int Htto::Rational_fraction::get_int_value()
{
	return (int)m_molecular;
}
#endif

Rational_fraction Htto::operator-( Rational_fraction param)
{
	param.m_molecular = -param.m_molecular;
	return param;
}
