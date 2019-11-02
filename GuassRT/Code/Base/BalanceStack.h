#ifndef BALANCESTACK_H_
#define BALANCESTACK_H_
#include "Count.h"
#include <stack>
namespace Htto
{
	class BalanceStack
	{
	private:
		std::string data;
		std::stack<char> container;
		size_t deep;
	public:
		BalanceStack(const std::string & parameter) :data(parameter), deep(0)
		{

		}
		bool checkBalance();
		void Reset(const std::string & parameter)
		{
			data = parameter;
		}
		int Deep() { if (checkBalance() == false)return 0;;return deep; }
	};
}
#endif