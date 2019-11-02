#pragma once
#include "polynomial.h"
#include "rational_fraction.h"
#include <stack>
#include <list>

namespace Htto
{
	namespace Count
	{
		int get_priority(char ch);
		struct unit
		{
			std::string strData;
			float numData;
			int priority;
			bool isNumber;
		};
		//实现一个小小的计算器。
		template <typename T>
		struct Element
		{
			Element(std::string str, bool isNum,int p=0):priority(p)
			{
				strData = str;
				if (isNum)
				{
					isNumber = true;
					data = T(str);
				}
				else
				{
					isNumber = false;
					data = T();
				}
			}
			std::string strData;
			T data;
			int priority;
			bool isNumber;

		};
		template <typename T>
		struct ExpressionList
		{
			ExpressionList() = default;
			ExpressionList(std::list<T> lst)
			{
				for (auto & a:lst)
					data.push_back(Element<T>(a.strData,a.isNumber,a.priority));
			}
			ExpressionList(const std::list<Element<T>> & lst):data(lst) {  }
			void Add(const std::list<Element<T>> & lst) { data.push_back(lst); }
			std::list<Element<T>> data;
			void push_back(const Element<T> & t)
			{
				data.push_back(t);
			}
			void clear() { data.clear(); }
			std::list<Element<T>> to_list()const { return data; }
			T & begin() { return data.begin(); }
			T& end() { return data.end(); }
			//void operator++() { data++; }
#ifdef CONSOLE_DEBUG
			void debug()
			{
				std::cout << "DEBUG Start:print all elements\n";
				for (const auto & a : data)
				{
					std::cout << a.strData <<"      Priority:"<<a.priority<< std::endl;
				}
				std::cout << "And size is: ";
				std::cout << data.size() << std::endl << "End Debug.";
			}
#endif
		};
		class SimpleCount
		{
		public:
			static Rational_fraction Rational_fraction_count(const std::string& str);
			static Polynomial PolyCount(const std::string& str);
			static bool IsCountSign(char c);
			static Count::ExpressionList<Htto::Rational_fraction>PushToListR(const std::string & str);
			static Count::ExpressionList<Htto::Polynomial>PushToListP(const std::string & str);
			static std::list<unit> PushToListF(std::string input);
			static std::list<unit> InfixToPostfix(std::list<unit> & ExpStream);
			static Htto::Fraction GetCountResult(const std::list<unit> & exp);
			static Htto::Fraction Count(const std::string str);
		};
		//以上是基于Fraction的Count,下面使用模板写一个通用Count
		//注:T必须有一个接受std::string的构造函数
		template <typename T>
		class UniversalCount
		{
		public:
			UniversalCount() = default;
			UniversalCount(const ExpressionList<T> & explist) :data(explist) {}
			void Add(const ExpressionList<T> & explist) { data.Add(explist.data); }
			void InfixToPostfix(const ExpressionList<T> & explist);
#ifdef CONSOLE_DEBUG
			void debug() { data.debug(); }
#endif
			T Count()
			{
				T ret;
				T tp1;
				T tp2;
				std::stack<T> Stack;
				std::list<Element<T>> ExpStream = data.to_list();
				for (const auto & a :ExpStream)
				{
					if (a.isNumber)
					{
						Stack.push(T(a.data));
					}
					else
					{
						if (a.strData == "+")
						{
							tp2 = Stack.top();
							Stack.pop();
							tp1 = Stack.top();
							Stack.pop();
							Stack.push(tp1 + tp2);
						}
						else if (a.strData == "-")
						{
							tp2 = Stack.top();
							Stack.pop();
							tp1 = Stack.top();
							Stack.pop();
							Stack.push(tp1 - tp2);

						}
						else if (a.strData == "*")
						{
							tp2 = Stack.top();
							Stack.pop();
							tp1 = Stack.top();
							Stack.pop();

							Stack.push(tp1 * tp2);
						}
						else if (a.strData == "/")
						{
							tp2 = Stack.top();
							Stack.pop();
							tp1 = Stack.top();
							Stack.pop();

							Stack.push(tp1 / tp2);
						}
						else if (a.strData == "^")
						{
							T tp3 = Stack.top();
							Stack.pop();
							tp1 = Stack.top();
							Stack.pop();
							tp1 = Htto::SimpleAlgorithm::Pow(tp1, tp3);
							Stack.push(tp1);
						}
					}
				}
				ret = Stack.top();
				ret.simplification();
				return ret;
			}
		private:
			ExpressionList<T> data;
		};

		template<typename T>
		inline void UniversalCount<T>::InfixToPostfix(const ExpressionList<T>& explist)
		{
			data.clear();
			std::list<Element<T>> ExpStream=explist.to_list();
			std::list<Element<T>> output;
			std::stack<Element<T>> Stack;
			for (auto & index : ExpStream)
			{
				//当读入一个操作数时立即将他放到输出中.
				if (index.priority == 0)
				{
					output.push_back(index);
					continue;
				}
				//如果见到左括号我们将其推倒栈中.
				if (index.strData == "(")
				{
					Stack.push(index);
				}
				//a+b*c+(d*e+f)*g
				//如果见到右括号,那么就将栈元素弹出,将弹出的符号知道我们的左括号为止.
				else if (index.strData == ")")
				{
					while (!Stack.empty()&&Stack.top().strData != "(")
					{
						output.push_back(Stack.top());
						Stack.pop();
					}
					if(!Stack.empty())
						Stack.pop();
				}
				else
				{
					while (!Stack.empty() && index.priority <=Stack.top().priority)
					{
						output.push_back(Stack.top());
						Stack.pop();
					}
					Stack.push(index);
				}
			}
			while (!Stack.empty())
			{
				output.push_back(Stack.top());
				Stack.pop();
			}
			data = ExpressionList<T>(output);
		}
	}
}