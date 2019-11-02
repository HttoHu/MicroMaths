#pragma once
#include "simple_algorithm.h"
#include <string>
#include <vector>
#include <iostream>
#include <initializer_list>
namespace Htto
{
	class Radical_Number;
	class Radical_Exp;
	class Radical_Number
	{
	private:
		friend class Radical_Exp;
		friend Radical_Number operator-(Radical_Number op);
		long inNumber=1;
		long outNumber=1;
	public:
		Radical_Number(int front, int in) :outNumber(front), inNumber(in) {}
		Radical_Number(std::string str);
		Radical_Number() { Radical_Number(1, 1); };

		Radical_Number(int num) { Radical_Number(num, 1); };
		void simplification();//化简
		float get_numsqrt()const;
		void numsqrt();//开方
		std::string ToString()const;//输出string
#ifdef DEBUG
		void displayDEG()
		{
			std::
				<< "frontNumber:" << outNumber << "\t";
			std::cout << "insideNumber:" << inNumber << "\n";
		}
#endif
		int inNum();
		int outNum();
		Radical_Number StrSimpleCount(std::string str);
		Radical_Number set(std::string setStr);
		//=====================operator===========================
		Radical_Exp operator+(const Radical_Number & op)const;
		Radical_Exp operator-(const Radical_Number & op)const;
		Radical_Number operator*(const Radical_Number & op)const;
		Radical_Number operator/(const Radical_Number & op)const;
		Radical_Number operator= (const int & num);
		//====================class-type conversions===================
		operator Radical_Exp()const;
		operator float()const;
		operator std::string()const;
		operator int()const;
	};
	class Radical_Exp
	{
	private:
		friend class Fraction;
		friend class Radical_Number;
		std::vector<Radical_Number> ExpVec;
	public:
		Radical_Exp() = default;
		Radical_Exp(std::string str);
		Radical_Exp(std::initializer_list<Radical_Number> RNL) { for (auto  au : RNL) { ExpVec.push_back(au); } }
		std::string ToString()const;
		float get_numsqrt()const;
		void reset(std::string str);
		void simplification();
		void reduceByNumber(int num);
		bool isSingle();
		bool isNature();
		//==============================运算====================================
		/*部分方法尚未编辑关于Exp和Number之间的运算你可以显示的将Number转换为Exp*/
		friend Radical_Exp operator-(Radical_Exp op);//求根式相反数
		Radical_Exp operator+(Radical_Exp Exp)const;
		Radical_Exp operator-(Radical_Exp Exp)const;
		Radical_Exp operator*(Radical_Exp op)const;
		Radical_Exp operator* (Radical_Number op)const;
		//没有除法???当然目前没有
		int GetMaxGCD();
		//=============================class-type conversion===================
		operator float()const;//convert into a float type
	};
	class Fraction
	{
	private:
		friend Fraction operator-(const Fraction fra);
		//分子
		Radical_Exp m_molecular;
		//分母
		Radical_Exp m_denomilator;
	public:
		Fraction():m_denomilator("1"),m_molecular("0"){ }
		Fraction(Radical_Exp up, Radical_Exp under);
		Fraction(std::string str);
		Fraction(int a, int b);
		Fraction(float fla);
		Fraction(const Fraction & fra);
		Fraction(Fraction && fra)noexcept = default;
		Fraction& operator= (const Fraction & fra);
		//======================常用操作====================
		Fraction pow(int times);//计算这个的times次方
		Fraction get_sqrt_value()const;
		void numsqrt();//开方.
		void simplification();//化简
		void reciprocal();//取倒数
		Fraction get_reciprocal()const;//记住这个函数性能可以更好。
		std::string ToString()const;//换为String
		bool is_interger()const;
	    bool is_square()const;
		float get_float_value()const;
		//=================operator=========================
		Fraction operator+(const Fraction & op)const;
		Fraction& operator+=(const Fraction & op);
		Fraction& operator-=(const Fraction & op);
		Fraction operator-(const Fraction & op)const;
		Fraction operator*(const Fraction & op)const;
		Fraction operator/(const Fraction & op)const;
		bool operator==(const Fraction & op)const;
		bool operator<(const Fraction & op)const;
		bool operator>(const Fraction & op)const;
		bool operator<=(const Fraction & op)const;
		bool operator>=(const Fraction & op)const;
		operator float()const;
	};
}
