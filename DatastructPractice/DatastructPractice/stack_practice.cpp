
#include"stack_practice.h"

void convert(mystd::Stack<char>* s, int64_t data, int base)
{
	static char digit[] =
	{ '0','1','2','3','4','5','6','7','8','9','10','A','B','C','D','E','F' };
	mystd::Stack<char> s0;
	while (data)
	{
		s0.push(digit[data%base]);
		data /= base;
	}
	while (!s0.empty())
	{
		s->push(s0.top());
		s0.pop();
	}
}

bool branketCheck(const char * p)
{
	char const *p_temp =p;
	mystd::Stack<char> s;
	while (*p_temp)
	{
		switch (*p_temp)
		{
			case '{':
			case '[':
			case '(':
				s.push(*p_temp);
				break;
			case '}':
				if (s.empty() || s.top() != '{')
					return false;
				s.pop();
				break;
			case ']':
				if (s.empty() || s.top() != '[')
					return false;
				s.pop();
				break;
			case ')':
				if (s.empty() || s.top() != '(')
					return false;
				s.pop();
				break;
			default:
				break;
		}
		++p_temp;
	}
	if (!s.empty())
		return false;
	return true;
}
