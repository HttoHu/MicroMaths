#include "../BalanceStack.h"

#include "pch.h"
 

int getCharValue(char ch)
{
	if (ch == '(')
		return 1;
	else if (ch == ')')
		return -1;
	else if (ch == '[')
		return 2;
	else if (ch == ']')
		return -2;
	else
		return 0;
}
bool Htto::BalanceStack::checkBalance()
{
	for (auto a : data)
	{
		if (getCharValue(a) == 0)
			continue;
		else if (getCharValue(a) == 1 || getCharValue(a) == 2)
		{
			container.push(a);
			if (container.size() > deep)
				deep = container.size();
		}
		else if (getCharValue(a) == -1)
		{
			if (getCharValue(container.top()) == 1)
			{
				container.pop();
				continue;
			}
			else
				return false;
		}
		else if (getCharValue(a) == -2)
		{
			if (getCharValue(container.top()) == 2)
			{
				container.pop();
				continue;
			}
			else
				return false;
		}
	}
	return true;
}

