#include <string>
#include <cmath>
#include <limits.h>

using namespace std;

bool isDigit (char c)
{
	return (c >= '0' && c <= '9');
}

int atoi(string str) 
{
	string s("");
    for (int i = 0; i < str.size(); ++i)
    {
		// handle corner case, no need to focus on ... 
		if (!isDigit(str[i]))
		{
			if (s.size() == 0)
			{
				if (str[i] == '-' || str[i] == '+' )
					s += str[i];
			}
			else // already has chars, which mean i must > 0
			{
				if (isDigit(str[i-1]))
					break;
				else
					return 0;	// "+-" or "-+" .. 
			}
		}
		// normal case
		if (isDigit(str[i]))
			s += str[i];
    }
    // take the pure number part    
    bool isNegative = false;
    if (s[0] == '-')
	{
        s = s.substr(1,s.size());       // "-12" --> "12"
		isNegative = true;
	}
	if (s[0] == '+')
	{
		s = s.substr(1,s.size());
	}
    // computing the numbers ... 
    long res = 0;
    int power = s.size() - 1;
    for (int i = 0; i < s.size(); ++i)
    {
        int digit = s[i] - '0';
        res += digit * std::pow(10, power) ;  
        power--;
    }           
    if (isNegative)
        res *= -1;
    if (res > INT_MAX)
        return INT_MAX;
    else if (res < -INT_MIN)
        return -INT_MIN;
    else
        return (int)res;
}