#include <iostream>
#include <vector>

#include "FrogJump.h"
#include "NumberSolitaire.h"
#include "Real_ParitionThree.h"
#include "Real_StackOperation.h"
#include "Real_PhoneNumber.h"

using namespace std;

int getValue(int i)
{
    if (i == 0) return 0;
    int count = 1;
    int res = 0;
    while (count <= i)
    {
        res += res + count;
        count++;    
    }
    return res;
}
#include <set>
string increament(string& s)
{
    string res = s;    
    int adv = 0;
    if (s[7] < '9')
    {
        res[7] = char(res[7] + 1);
        return res;
    }   
    if (s[7] == '9')
    {
        res[7] = '0';
        adv = 1;
    }
    if (s[6] < '5' && adv)
    {       
        res[6] = char(res[6] + 1);
        return res;
    }
    if (s[6] == '5' && adv)
    {
        res[6] = '0';
	}
    if (s[4] < '9' && adv)
    {       
        res[4] = char(res[4] + 1);
        return res;
    }
    if (s[4] == '9' && adv)
    {
        res[4] = '0';
	}
    if (s[3] < '5' && adv)
    {       
        res[3] = char(res[3] + 1);
        return res;
    }
    if (s[3] == '5' && adv)
    {
        res[3] = '0';
	}

	if (s[0] == '1')
	{
		if (s[1] < '9' && adv)
		{       
			res[1] = char(res[1] + 1);
			return res;
		}
		if (s[1] == '9' && adv)
		{
			res[1] = '0';
			res[0] == '2';
			return res;
		}
	}
	else 
	{
		if (s[1] < '3' && adv)
		{
			res[1] = char(res[1] + 1);		
		}
	}
    return res;
}

bool isTwoDigits(string& s)
{
	string digits("");
	digits += s[0];
	digits += s[1];
	digits += s[3];
	digits += s[4];
	digits += s[6];
	digits += s[7];
	set<int> set;
	set.insert(digits[0]);
	for (int i = 1; i < digits.size(); ++i)
	{
		if (digits[i] != digits[i-1])
		{
			set.insert(digits[i]);
			if (set.size() > 2)
				return false;
		}
	}
	return true;
}

int solution1(string &S, string &T) 
{
    if (S == T) return 0;
    
    int res = 0;
    
    while(S != T)
    {
        string s = increament(S);
        if (isTwoDigits(s)) 
            res++;
        S = s;        
    }
    return res;
}


int main () 
{
	//int A[6] = {1,3,1,4,2,5};
	//std::cout << solution(A, 6,7,3) << std::endl;

	//vector<int> B(7,0);
	//B[0] = 3;
	//B[1] = 4;
	//B[2] = 4;
	//B[3] = 6;
	//B[4] = 1;
	//B[5] = 4;
	//B[6] = 4;

	//vector<int> vec = solution2(5,B);
	//for (int i = 0; i < B.size(); ++i)
	//	cout << B[i] << endl;


	//// Test Case for NumberSolitaire
	//int arr[] = {-2,5,1};
	//vector<int> A (arr, arr + sizeof(arr)/ sizeof(int));
	//cout << solution(A) << endl;
	////


	//// Test Case for Partition Three
	//int arr1[] = {1,3,3,5,6,7,8,1,2,3,2,4};
	//vector<int> ivec(arr1, arr1+sizeof(arr1)/sizeof(int));
	//cout << PartitionThree(ivec) << endl;

	
	string s = "00:00:59";
	cout << s[7] << endl;

	//char s[] = "13+62*7";
	//char c[] = "0 - 22 1985--324";
	//char c1[] = "00-44  48 5555 8361";
	//cout << FormatPhoneNumber(c1) << endl;

	//cout << StackOperation("13+62*7+*") << endl;
	cout << (int)"59" << endl;

	cout << getValue(3) << endl;

	//cout << (char)((int)('6' - '0') + 1) << endl;
	//cout << static_cast<char>(((int)('6' - '0') + 1) - '0') << endl;
	string str = "13:59:59";
	int i = '3' + 1;

	cout << char('0'+1) << endl;
	string s1 = "15:15:10";
	string s2 = "15:15:12";
	cout << solution1(s1, s2) << endl;
	getchar();
	return 0;
}
