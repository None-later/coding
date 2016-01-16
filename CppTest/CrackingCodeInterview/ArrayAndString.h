#include <string> 

using namespace std;

//char FindHighestFreqChar(const string& s)
//{
//	int freq[26] = {0};
//	for (int i = 0; i < s.size(); ++i)
//	{
//		if (s[i] >= 'a' && s[i] <= 'z')
//			freq[s[i] - 'a']++;
//	}
//
//	char res = 'a';
//	int maxFreq = freq[0];
//	for (int i = 1; i < 26; i++)
//	{
//
//		if (freq[i] > maxFreq)
//		{
//			maxFreq = freq[i];
//			res = (char)('a' + i);
//		}
//	}
//	return res;
//}

//// Crack Code 1.3
//void reverseString(char* s)
//{
//	int beg = 0;
//	int end = strlen(s)-1;
//
//	while(beg < end)
//	{
//		char tmp = *(s + beg);
//		*(s + beg) = *(s + end);
//		*(s + end) = tmp;
//		beg++;
//		end--;
//	}
//}

//// Crack Code 1.4
//#include <sstream>
//#include <vector>
//string filledSpace(string& s)
//{
//	string res("");
//	vector<string> svec;
//	stringstream ss(s);
//	string tok;
//	while (ss >> tok)
//	{
//		svec.push_back(tok);
//	}
//	for (size_t i = 0; i < svec.size(); ++i)
//	{
//		if (i == 0)
//			res += svec[i];
//		else
//		{
//			res += "%20";
//			res += svec[i];
//		}
//	}
//	return res;
//}

//// Crack Code 1.5
//string CompressedString(const char* s)
//{
//	if (strlen(s) <= 1)
//		return s;
//
//	string res("");
//	res += s[0];
//	int count = 1;
//	for (int i = 1; i < strlen(s); ++i)
//	{
//		if (s[i] == s[i-1])
//		{
//			count++;
//		}
//		else
//		{
//			res += std::to_string(count);
//			res += s[i];
//			count = 1;
//		}
//	}
//	res += to_string(count);
//	return (res.size() < strlen(s))? res : s;
//}


// Crack Code 1.6
void rotateImage(int (&image)[5][5])
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = i+1; j < 5; ++j)
		{
			int temp = image[i][j];
			image[i][j] = image[j][i];
			image[j][i] = temp;
		}
	}
}