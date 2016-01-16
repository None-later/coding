#include <vector>

// Required : Time O(n), Space O(n)
/*
The key point is: to achieve the position i, 
we can only come from the positions i-6, i-5, i-4, i-3, i-2, and i-1.

rollingMax = max(MaxSoFar over the past 6 index)

		value	rollingMax	MaxSoFar(value + currMax)		
A[0]	 1		1			 1
A[1]	-2		1			-1
A[2]	 0		1			 1	
A[3]	 9		1			10
A[4]	-1		10			 9
A[5]	-2		10			 8
A[6]	-3      10			 7
A[7]	-4      10           6
A[8]    -1      10			 9
A[9]	-1      10           9
A[10]   -1      9            8  
*/

int solution(std::vector<int> &A) 
{
	std::vector<int> padding(6,A[0]);         
	std::vector<int> maxSoFar(A.size(), A[0]); 
	maxSoFar.insert(maxSoFar.begin(), padding.begin(), padding.end());
	A.insert(A.begin(), padding.begin(), padding.end());
  
	for (int i = 7; i < A.size(); ++i)
	{
		int rollingMax = maxSoFar[i-1];
		for (int j = i-2; j >= i-6; --j)
		{
			rollingMax = std::max(rollingMax, maxSoFar[j]);
		}
		maxSoFar[i] = A[i] + rollingMax;
	}
    return maxSoFar[A.size() - 1];
}