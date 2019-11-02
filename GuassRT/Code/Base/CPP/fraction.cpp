#include "../fraction.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "pch.h"
 
using namespace Htto;
using std::string;
using std::cout;
using std::vector;
//===============一些野生函数=====================
bool isR1R2(char ch)
{
	return ch == '+' || ch == '-';
}
unsigned int SearchR1R2(string str, unsigned int index)
{
	unsigned int oldV = str.size();
	str = str.substr(index);
	for (auto au : str)
	{
		if (isR1R2(au))
			return index;
		index++;
	}
	return oldV + 1;
}
//==================一些构造函数啥的================
Htto::Radical_Exp::Radical_Exp(std::string str)
{
	std::string temp = "";
	/*
	unsigned int index = 0;
	string ache;
	while (index < str.size())
	{
	int oindex = index;
	index = SearchR1R2(str, index+1);
	string echo = str.substr(oindex, index - oindex);
	numberPart.push_back(echo);
	}
	Radical_Number Transform;
	for (unsigned int i = 0;i < numberPart.size();i++)
	{
	Transform = Transform.StrSimpleCount(numberPart[i]);
	//std::cout << numberPart[i]<<"\n\n";
	ExpVec.push_back(Transform);
	}
	*/
	int state = 0;
	for (const auto & a : str)
	{
		if (a == '+')
			state = 2;
		else if (a == '-')
			state = 3;
		else
			state = 0;
		switch (state)
		{
		case 0://普通状态
			temp += a;
			break;
		case 2://遇到+号
			if (temp == "")
				continue;
			else
			{
				ExpVec.push_back(Radical_Number(temp));
				temp = "";
			}

			break;
		case 3://遇到-号.
			if (temp == "")
			{
				temp += a;
				continue;
			}
			else
			{
				ExpVec.push_back(Radical_Number(temp));
				temp = "";
				temp += a;
				continue;
			}
		default:
			break;
		}
	}
	if (temp != "")
		ExpVec.push_back(Radical_Number(temp));

}
std::string Htto::Radical_Exp::ToString()const
{
	string ret = "";
	for (auto au : ExpVec)
	{
		if (au.ToString()[0] == '-')
			ret += au.ToString();
		else
			ret += '+' + au.ToString();
	}
	if (ExpVec[0].ToString()[0] == '-')
	{
		return ret;
	}
	else
	{
		if (ret.substr(0, 1) != "@")
			return ret.substr(1);
		else
			return ret.substr(2);
	}

}
float Htto::Radical_Exp::get_numsqrt() const
{
	float ret=0.0;
	for (const auto & a : ExpVec)
	{
		ret += a.get_numsqrt();
	}
	return ret;
}
void Htto::Radical_Exp::reset(string str)
{
	vector<string> numberPart;
	unsigned int index = 0;
	string ache;
	while (index < str.size())
	{
		int oindex = index;
		index = SearchR1R2(str, index + 1);
		string echo = str.substr(oindex, index - oindex);
		numberPart.push_back(echo);
	}
	Radical_Number Transform;
	for (unsigned int i = 0;i < numberPart.size();i++)
	{
		Transform = Transform.StrSimpleCount(numberPart[i]);
		ExpVec.push_back(Transform);
	}
}
void Htto::Radical_Exp::simplification()
{
	for (auto & au : ExpVec)
	{
		au.simplification();
	}
	std::sort(ExpVec.begin(), ExpVec.end(), [](Radical_Number rn, Radical_Number rn2) {return rn.inNum() > rn2.inNum();});
	vector <Radical_Number>newRNVec;
	Radical_Number TPRN;
	//======================================
	Radical_Number ResultNum;
	std::size_t index = 1;
	vector<Radical_Number>tp;
	for (auto au : ExpVec)
	{
		tp.push_back(au);
	}
	while (index < tp.size())
	{
		if (tp[index].inNumber == tp[index - 1].inNumber)
		{
			ResultNum.outNumber = tp[index].outNumber + tp[index - 1].outNumber;
			if (ResultNum.outNumber == 0)
			{
				tp.erase(tp.begin() + index);
				tp.erase(tp.begin() + index - 1);
				index++;
				continue;
			}
			ResultNum.inNumber = tp[index].inNumber;
			tp.erase(tp.begin() + index);
			tp.erase(tp.begin() + (index - 1));
			tp.insert(tp.begin() + (index - 1), ResultNum);
			continue;
		}
		index++;
	}
	ExpVec = tp;
	//======================================
}
void Htto::Radical_Exp::reduceByNumber(int num)
{
	for (auto & au : ExpVec)
	{
		au.outNumber /= num;
	}
}
bool Htto::Radical_Exp::isSingle()
{
	return !(bool)(ExpVec.size() - 1);
}
bool Htto::Radical_Exp::isNature()
{
	simplification();
	if (!isSingle())
		return false;
	if (ExpVec[0].inNum() == 1)
	{
		return true;
	}
	else
		return false;
}
Htto::Radical_Exp Htto::Radical_Exp::operator+ (Radical_Exp Exp)const
{
	Radical_Exp tp;
	for (auto auo : Exp.ExpVec)
	{
		tp.ExpVec.push_back(auo);
	}
	for (auto auo : ExpVec)
	{
		tp.ExpVec.push_back(auo);
	}
	tp.simplification();
	return tp;
}
Radical_Exp Htto::Radical_Exp::operator-(Radical_Exp Exp)const
{
	Exp = -Exp;
	return *this + Exp;
}
Radical_Exp Htto::Radical_Exp::operator*(Radical_Exp op)const
{
	Radical_Exp ret;
	Radical_Exp newRE;
	//cout << op.ToString();
	for (auto au : ExpVec)
	{
		newRE = op*au;
		ret = ret + newRE;
	}
	ret.simplification();
	return ret;
}
Radical_Exp Htto::Radical_Exp::operator*(Radical_Number op)const
{
	Radical_Exp newRE;
	for (auto au : ExpVec)
	{
		newRE.ExpVec.push_back(op*au);
	}
	return newRE;
}
int Htto::Radical_Exp::GetMaxGCD()
{
	simplification();
	int maxGcd = ExpVec[0].outNumber;
	for (unsigned int i = 1;i < ExpVec.size();i++)
	{
		maxGcd = SimpleAlgorithm::INT_GCD(maxGcd, ExpVec[i].outNumber);
	}
	if (maxGcd < 0)
		return -maxGcd;
	else
		return maxGcd;

}
Htto::Radical_Exp::operator float() const
{
	float sum = 0.0;
	for (auto au : ExpVec)
	{
		sum += (float)au;
	}
	return sum;
}
//======================op=======================
//================ for Radical_Number====野生函数============
bool isSquareNumber(int);
int red(int);
std::string NumToStr(int n)
{
	return std::to_string(n);
}
int StrToNum(std::string str);
//==================================
int red(int r)
{
	for (int i = 2;i <= r;i++)
	{
		if ((r%i) == 0 && isSquareNumber(i))
		{
			return i;
		}
	}
	return 1;
}//获得最大平方因数
 //===================================
int StrToNum(std::string str)
{
	int number = std::atoi(str.c_str());
	if (errno == ERANGE) //可能是std::errno
	{
		return 0;
	}
	return number;
}
//================================
bool isSquareNumber(int n)
{
	for (int i = 1;n > 0;i += 2)
		n -= i;
	return !((bool)n);
}
Htto::Radical_Number::Radical_Number(std::string str)
{
/*old
bool isNa;
if (str[0] == '+')
{
str = str.substr(0);
isNa = false;
}
else if (str[0] == '-')
{
str = str.substr(1);
isNa = true;
}
if (str.find("@") == std::string::npos)
{
outNumber = StrToNum(str);
inNumber = 1;
return;
}
unsigned int index = str.find("@");
if (index == 0)
{
outNumber = 1;
inNumber = StrToNum(str.substr(index + 1));
if (isNa)
outNumber = -outNumber;
return;
}
outNumber = StrToNum(str.substr(0, index));
inNumber = StrToNum(str.substr(index + 1));
if (isNa)
{
outNumber = -outNumber;
}*/
	//要知道改动以前的函数是十分具有风险的.
	int state = 0;
	bool test = false;
	std::string temp;
	for (const auto & a : str)
	{
		if (isdigit(a))
		{
			state = 0;
		}
		else if (a == '@')
		{
			test = true;
			state = 1;
		}
		switch (state)
		{
		case 0:
			temp += a;
			break;
		case 1:
			if (temp != "")
			{
				outNumber = StrToNum(temp);
				temp = "";
			}
			break;
		default:
			break;
		}

	}
	if (!test&&temp!="")
	{
		outNumber = StrToNum(temp);
		inNumber = 1;
		return;
	}
	if (temp != "")
		inNumber = StrToNum(temp);
	else
		inNumber = 1;
}
//化简函数
void Htto::Radical_Number::simplification()
{
	int tempNumber = red(inNumber);
	if (tempNumber == 0)
	{
		outNumber = 0;
		inNumber = 0;
		return;
	}
	outNumber *= (int)sqrt(tempNumber);
	inNumber /= tempNumber;
}
float Htto::Radical_Number::get_numsqrt()const
{
	return outNumber*sqrt(inNumber);
}
void Htto::Radical_Number::numsqrt()
{
	if (inNumber != 1)
	{
		throw;
		return;
	}
	else
	{
		inNumber = outNumber;
		outNumber = 1;
	}
}
//ToString()
std::string Htto::Radical_Number::ToString()const
{
	std::string front = NumToStr(outNumber);
	std::string inner = NumToStr(inNumber);
	std::string bond = "@";
	if (inNumber == 1)
	{
		return front;
	}
	else if (outNumber == 1)
	{
		return bond + inner;
	}
	else if (outNumber == -1)
	{
		return "-" + bond + inner;
	}
	else
	{
		return front + bond + inner;
	}
}
int Htto::Radical_Number::inNum()
{
	return inNumber;
}
int Htto::Radical_Number::outNum()
{
	return outNumber;
}
Radical_Number Htto::Radical_Number::StrSimpleCount(std::string str)
{
	unsigned int index;
	if (str.find('*') == std::string::npos && str.find('/') == std::string::npos)
		return set(str);
	else if (str.find('*'))
	{
		index = str.find('*');
		std::string p1;
		std::string p2;
		p1 = str.substr(0, index);
		p2 = str.substr(index + 1);
		Radical_Number R1(p1);
		Radical_Number R2(p2);
		return R1*R2;
	}
	else if (str.find('/'))
	{
		index = str.find('/');
		std::string p1;
		std::string p2;
		p1 = str.substr(0, index);
		p2 = str.substr(index + 1);
		Radical_Number R1(p1);
		Radical_Number R2(p2);
		return R1 / R2;
	}
	else
	{
		throw std::runtime_error("an illegal expression");
	}
}
Radical_Number Htto::Radical_Number::set(std::string setStr)
{
	std::string & str = setStr;
	if (setStr.find("@") == std::string::npos)
	{
		outNumber = StrToNum(setStr);
		inNumber = 1;
		return *this;
	}
	bool isNa = false;
	if (str[0] == '+')
	{
		str = str.substr(1);
		isNa = false;
	}
	else if (str[0] == '-')
	{
		str = str.substr(1);
		//std::cout << "\n   " << str << "fas\n";
		isNa = true;
	}
	if (str.find("@") == std::string::npos)
	{
		outNumber = StrToNum(str);
		inNumber = 1;
		return *this;
	}
	unsigned int index = str.find("@");
	if (index == 0)
	{
		outNumber = 1;
		inNumber = StrToNum(str.substr(index + 2));
		if (isNa)
			outNumber = -outNumber;
		return *this;
	}
	outNumber = StrToNum(str.substr(0, index));
	inNumber = StrToNum(str.substr(index + 2));
	if (isNa)
	{
		outNumber = -outNumber;
	}
	return *this;
}
Radical_Exp Htto::Radical_Number::operator-(const Radical_Number & op)const
{
	int in;
	int out;
	if (inNumber == op.inNumber)
	{
		in = inNumber;
		out = outNumber - op.outNumber;
	}
	else
	{
		return Radical_Exp();
	}
	Radical_Number TPRN(out, in);
	return Radical_Exp({ TPRN });
}
Radical_Exp Htto::Radical_Number::operator+(const Radical_Number & op)const
{
	int in;
	int out;
	if (inNumber == op.inNumber)
	{
		in = inNumber;
		out = outNumber + op.outNumber;
	}
	else
	{
		return Radical_Exp({ *this, op });
	}
	Radical_Number TPRN(out, in);
	return Radical_Exp({ TPRN });
}
//=======================op区==========================
Htto::Radical_Number Htto::Radical_Number::operator*(const Radical_Number & op)const
{
	int frontN = this->outNumber*op.outNumber;
	int inN = this->inNumber*op.inNumber;
	Radical_Number ret(frontN, inN);
	ret.simplification();//化简
	return ret;
}
Htto::Radical_Number Htto::Radical_Number::operator/(const Radical_Number & op)const
{
	if (op.outNumber == 0 || op.inNumber == 0)
		return Radical_Number();
	int frontN = this->outNumber / op.outNumber;
	int inN = this->inNumber / op.inNumber;
	Radical_Number ret(frontN, inN);
	ret.simplification();//化简
	return ret;
}
Radical_Number Htto::Radical_Number::operator=(const int & num)
{
	this->outNumber = num;
	this->inNumber = 1;
	return *this;
}
Htto::Radical_Number::operator Radical_Exp() const
{
	return Radical_Exp({ *this });
}
Htto::Radical_Number::operator float() const
{
	return (float)(outNumber*sqrt(inNumber));
}
Htto::Radical_Number::operator std::string() const
{
	return ToString();
}
Htto::Radical_Number::operator int() const
{
	return outNumber*(int)sqrt(inNumber);
}
Radical_Number Htto::operator-(Radical_Number op)
{
	op.outNumber = -op.outNumber;
	return op;
}
Radical_Exp Htto::operator-(Radical_Exp  op)
{
	for (auto &/*少了一个&符号我查了1个小时。。。。*/ au : op.ExpVec)
	{
		au = -au;
	}
	return op;
}


//========== TAB:AA3 class fraciton=============================

//一些构造函数=====================================
Htto::Fraction::Fraction(Radical_Exp up, Radical_Exp under)
{
	m_molecular = up;
	m_denomilator = under;
}
Htto::Fraction::Fraction(std::string str)
{
	if (str[0] == '(')
	{
		str = str.substr(1, str.size() - 2);
	}
	//这是我以前的手法,分割字符大法然后针对各个情况进行分析,效率比较低bug比较多.Fraction很久之前就写的,修改起来很复杂.我现在只能确保它的正确性和稳定性.
	else if (str == "-")
	{
		m_molecular = Radical_Exp("-1");
		m_denomilator = Radical_Exp("1");
		return;
	}
	else if (str == "+")
	{
		m_molecular = Radical_Exp("1");
		m_denomilator = Radical_Exp("1");
		return;
	}
	if (str.find('/') == std::string::npos&&str.find('@')==std::string::npos)
	{
		float fla=StringTools::string_to_float(str);
		int test = fla;
		int tenV = 1;
		while (1)
		{
			if (SimpleAlgorithm::isEqual(test, fla))
			{
				m_molecular = Radical_Exp(std::to_string(test));
				m_denomilator = Radical_Exp(std::to_string(tenV));
				simplification();
				return;
			}
			else
			{
				tenV *= 10;
				fla *= 10;
				test = fla;
			}
		}
		return;
	}
	string tpstr = Htto::StringTools::get_rid_of_parentheses(str);//这是什么???? 问问半年前的我????????
	if (tpstr.find('/') == std::string::npos&&tpstr.find('(')!=std::string::npos)//然后我就看不懂了,去除括号吗...先不管他应该是对的.
	{
		string init = Htto::StringTools::get_match_content(str);
		Fraction tp = Fraction(init);
		tp.numsqrt();
		m_denomilator = tp.m_denomilator;
		m_molecular = tp.m_molecular;
		simplification();
		return;
	}
	else if (str.find('/') == std::string::npos&&tpstr.find('@') != std::string::npos)
	{
		m_molecular = Radical_Exp(str);
		//std::cout << str;
		m_denomilator = Radical_Exp("1");
		return;
	}
	size_t index = str.find('/');
	string upper = str.substr(0, index);
	string under = str.substr(index + 1);
	m_molecular = Radical_Exp(upper);
	m_denomilator = Radical_Exp(under);

}
Htto::Fraction::Fraction(int a, int b)
{
	if (b == 0)
	{
		throw std::runtime_error("Fraction(int a,int b):m_denomilator cann't be zero");
	}
	m_molecular = NumToStr(a);
	m_denomilator = NumToStr(b);
}
Htto::Fraction::Fraction(float fla)
{
	int test = fla;
	int tenV = 1;
	while (1)
	{
		if (SimpleAlgorithm::isEqual(test, fla))
		{
			m_molecular = Radical_Exp(std::to_string(test));
			m_denomilator = Radical_Exp(std::to_string(tenV));
			simplification();
			return;
		}
		else
		{
			tenV *= 10;
			fla *= 10;
			test = fla;
		}
	}
}
Htto::Fraction::Fraction(const Fraction & fra)
{
	m_denomilator = fra.m_denomilator;
	m_molecular = fra.m_molecular;
}
Fraction& Htto::Fraction::operator=(const Fraction & fra)
{
	m_molecular = fra.m_molecular;
	m_denomilator = fra.m_denomilator;
	return *this;
}
//============================================
Fraction Htto::Fraction::pow(int times)
{
	if (times == 0)
	{
		return Fraction();
	}
	Fraction temp = *this;
	Fraction temp2=temp;
	int index = SimpleAlgorithm::ABS(times);
	for (int i = 1;i < index;i++)
	{
		temp = temp2*temp;
	}
	if (times < 0)
	{
		return Fraction("1")/temp;	
	}
	else
		return temp;
}
Fraction Htto::Fraction::get_sqrt_value()const
{
	Fraction ret = *this;
	ret.numsqrt();
	ret.simplification();
	return ret;
}
void Htto::Fraction::numsqrt()
{
	simplification();
	if ((int)(*this) < 0)
		throw std::runtime_error("try to sqrt a negetive fraction.");
	if (m_molecular.ExpVec.size() > 2 || m_denomilator.ExpVec.size() > 2)
	{
		return;
	}
	else if (m_molecular.ExpVec.size() == 1 && m_denomilator.ExpVec.size() == 1)
	{
		m_molecular.ExpVec[0].numsqrt();
		m_denomilator.ExpVec[0].numsqrt();
		if (!m_denomilator.isNature())
		{
			Radical_Exp tp = m_denomilator;
			m_denomilator = m_denomilator*tp;
			m_molecular = tp*m_molecular;
		}
	}
	else if (m_molecular.ExpVec.size() == 1 && m_denomilator.ExpVec.size() == 2)
	{
		Radical_Number rh = m_denomilator.ExpVec[0];
		Radical_Number lh = -m_denomilator.ExpVec[1];
		Radical_Exp t;
		t.ExpVec.push_back(rh);
		t.ExpVec.push_back(lh);
		m_molecular = m_molecular*t;
		m_denomilator = m_denomilator*t;
		simplification();
		numsqrt();
	}
}
void Htto::Fraction::simplification()
{
	//std::cout << Under.isNature();
	if (m_molecular.ExpVec.size() > 1 && (int)m_molecular.ExpVec.back() == 0)
	{
		m_molecular.ExpVec.pop_back();
	}
	if (m_denomilator == Radical_Exp("-1"))
	{
		m_denomilator = Radical_Exp("1");
		m_molecular = -m_molecular;
	}
	if (m_denomilator.isSingle() && !m_denomilator.isNature())
	{
		m_molecular = m_molecular*m_denomilator;
		m_denomilator = m_denomilator*m_denomilator;
	}
	m_molecular.simplification();
	m_denomilator.simplification();
	int maxGCD = SimpleAlgorithm::INT_GCD(m_molecular.GetMaxGCD(), m_denomilator.GetMaxGCD());
	m_molecular.reduceByNumber(maxGCD);
	m_denomilator.reduceByNumber(maxGCD);
}
void Htto::Fraction::reciprocal()
{
	if (m_denomilator == 0)
		throw std::runtime_error("zero cann't be m_denomilator");
	std::swap(m_denomilator, m_molecular);
}
Fraction Htto::Fraction::get_reciprocal()const
{
	Fraction ret = *this;
	if (m_denomilator == 0)
		throw std::runtime_error("zero cann't be m_denomilator");
	std::swap(ret.m_denomilator, ret.m_molecular);
	return ret;

}
string Htto::Fraction::ToString()const
{
	Fraction ret = *this;
	if (m_denomilator < Fraction(0))
	{
		ret.m_denomilator = -ret.m_denomilator;
		ret.m_molecular = -ret.m_molecular;
		return ret.ToString();
	}
	if (m_denomilator.ToString() == "1")
	{
		return m_molecular.ToString();
	}
	else if (m_molecular.ToString() == "0")
		return "0";
	else if (m_denomilator.ToString() == "0")
		throw std::runtime_error("Fraction: m_denomilator is zero");
	else if (m_denomilator.ToString() == "-1")
	{
		return "-" + m_molecular.ToString();
	}
	return  "("+m_molecular.ToString() + '/' + m_denomilator.ToString()+")";
}
bool Htto::Fraction::is_interger() const
{
	return float(*this) == (int)(*this);
}
bool Htto::Fraction::is_square()const
{
	if (std::sqrt((int)*this) == std::sqrt((float)*this))
	{
		return true;
	}
	return false;
}
//===========================重载的运算符=================
Fraction Htto::Fraction::operator+(const Fraction & op)const
{
	if (*this == -op)
	{
		return Fraction(0);
	}
	Radical_Exp under = m_denomilator*op.m_denomilator;
	Fraction f;
	f.m_molecular = (m_molecular*op.m_denomilator) + (op.m_molecular*m_denomilator);
	f.m_denomilator = under;
	f.simplification();
	return f;
}
Fraction& Htto::Fraction::operator+=(const Fraction & op)
{
	Radical_Exp under = m_denomilator*op.m_denomilator;
	m_molecular = (m_molecular*op.m_denomilator) + (op.m_molecular*m_denomilator);
	m_denomilator = under;
	simplification();
	return *this;
}
Fraction & Htto::Fraction::operator-=(const Fraction & op)
{
	Radical_Exp under = m_denomilator*op.m_denomilator;
	m_molecular = (m_molecular*op.m_denomilator) - (op.m_molecular*m_denomilator);
	m_denomilator = under;
	simplification();
	return *this;
}
Fraction Htto::Fraction::operator-(const Fraction & op)const
{
	Fraction f;
	Radical_Exp under = m_denomilator*op.m_denomilator;
	if (*this == op)
		return 0;
	f.m_molecular = (m_molecular*op.m_denomilator) - (op.m_molecular*m_denomilator);
	f.m_denomilator = under;
	f.simplification();
	return f;
}
Fraction Htto::Fraction::operator*(const Fraction & op)const
{
	Fraction f;
	f.m_denomilator = m_denomilator*op.m_denomilator;
	f.m_molecular = m_molecular*op.m_molecular;
	f.simplification();
	return f;
}
Fraction Htto::Fraction::operator/(const Fraction & op)const
{
	Fraction f;
	f.m_denomilator = m_denomilator*op.m_molecular;
	f.m_molecular = m_molecular*op.m_denomilator;
	f.simplification();
	return f;
}
bool Htto::Fraction::operator==(const Fraction & op)const
{
	return (get_float_value() == op.get_float_value());
}
bool Htto::Fraction::operator<(const Fraction & op)const
{
	return (get_float_value() < op.get_float_value());
}
bool Htto::Fraction::operator>(const Fraction & op)const
{
	return (get_float_value() > op.get_float_value());
}
bool Htto::Fraction::operator<=(const Fraction & op)const
{
	return (get_float_value() <= op.get_float_value());
}
bool Htto::Fraction::operator>=(const Fraction & op)const
{
	return (get_float_value() >= op.get_float_value());
}
Htto::Fraction::operator float()const
{
	return get_float_value();
}
float Htto::Fraction::get_float_value()const
{
	if (m_molecular == Radical_Exp("0"))
	{
		return 0.0;
	}
	return (float)m_molecular / (float)m_denomilator;
}

Fraction Htto::operator-(const Fraction fra)
{
	Fraction f;
	f = fra;
	f.m_denomilator = -f.m_denomilator;
	return f;
}
