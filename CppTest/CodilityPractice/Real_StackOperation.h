/*
A stack machine stores arbitrary 12-bit unsigned integers (0 ~ 2^12-1). Initially, the stack is empty. 
The machine processes a string of characters in the following ways:

> the char of string are processed one by one;
> if the char is digit('0' ~ '9'), the machine pushes the value of the digit to stack
> if the char is '+', the machine pops the two topmost values from the stack, adds them
and pushes the result back to the stack
> if the char is '*', pops top two and pushes back their multipply result
> after processing the whole string, returns the topmost value of the stack as the result
> the machine reports error and return -1 if :
	- overflows happens when doing multiplication and addition
	- tries to pop an element from the stack however its empty
	- after processing the whole string, the stack is empty 

assume that:
> the length of string is within range [0..200,000]
> the string contains the only following cahrs : 
'0' ~ '9','+','*'
*/
#include <stack>

using namespace std;

int StackOperation(char *s)
{
	int max = pow(2,12) - 1;
	stack<int> machine;
	while (*s != '\0')
	{
		if (*s >= '0' && *s <= '9')
		{
			machine.push((int)(*s - '0'));
		}
		else // '+' or '*'
		{
			if (machine.size() < 2)
				return -1;
			int x = machine.top();
			machine.pop();
			int y = machine.top();
			machine.pop();

			if (*s == '+')
			{
				if (max - x < y)
					return -1;
				machine.push(x+y);
			}
			if (*s == '*')
			{
				if (max / x < y)
					return -1;
				machine.push(x*y);
			}
		}
		s++;
	}
	return (!machine.empty()) ? machine.top() : -1;
}
