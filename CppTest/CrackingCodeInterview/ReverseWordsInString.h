#include <string>

using namespace std;

/*
	s = "the sky is blue"  --> "blue is sky the"

*/

string reverseWords(string &s) 
{
    string res("");
    int sEnd = s.size() - 1;
    	
    int subBeg;	
    int subEnd = s.size();	
    	
    for (int i = sEnd; i >= 0; --i)
    {
		if (s[i] == ' ')
		{
			subEnd = i;
		}
		else if (i == 0 || s[i-1] == ' ')
		{
			subBeg = i;
			if (res.size() != 0)
				res += ' ';
			res += s.substr(subBeg, subEnd-subBeg);
		}
    }
    return res;
}