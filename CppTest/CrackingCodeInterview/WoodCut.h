#include <vector>

using namespace std;

int getNumberOfCuts(const vector<int>& L, int length)
{
	int numCuts = 0;
	for (int i = 0; i < L.size(); ++i)
	{
		numCuts += (L[i] / length);
	}
	return numCuts;
}

int woodCut(vector<int> L, int k) 
{
	int numCuts = 0;
	int maxLen = 1;
	int minLen = 1;
	for (int i = 0; i < L.size(); ++i)
	{
		maxLen = max(maxLen, L[i]);
	}
	while (minLen + 1 < maxLen)
	{
		int mid = minLen + (maxLen - minLen) / 2;
		if (getNumberOfCuts(L, mid) >= k)  // length too short
		{
			minLen = mid;
		}
		else
		{
			maxLen = mid;
		}
	}
	if (getNumberOfCuts(L, maxLen) >= k)
	    return maxLen;  
	if (getNumberOfCuts(L, minLen) >= k)
	    return minLen;
	return 0;
}

