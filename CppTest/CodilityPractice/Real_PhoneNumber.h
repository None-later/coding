#include <string>

using namespace std;

string FormatPhoneNumber(char* s)
{
	string res("");
	int count = 0;
	for (int i = 0; i < strlen(s); i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			res += s[i];
			count++;
			if (count == 3)
			{
				res+= '-';
				count = 0;
			}
		}
	}
	if (count == 0)
	{
		res = res.substr(0, res.size()-1);
	}
	if (count == 1)
	{
		char c = res[res.size()-2];
		res[res.size()-2] = res[res.size()-3];
		res[res.size()-3] = c;
	}
	return res;
}