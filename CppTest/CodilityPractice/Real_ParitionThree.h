#include<vector>

using namespace std;

int PartitionThree(vector<int> ivec)
{
	if (ivec.size() == 5)
		return ivec[1] + ivec[3];

	int idx1 = 1, idx2 = 3;
	int leftSum = INT_MAX, left1 = ivec[idx1], left2 = ivec[idx2];
	// find best spot for idx2
	for (int i = 4; i <= ivec.size() - 2; i++)
	{
		if (ivec[i] <= left2)
		{
			idx2 = i;
			left2 = ivec[i];
		}
	}
	// find the spot for idx1
	for (int j = 2; j <= idx2 - 2; j++)
	{
		if (ivec[j] <= left1)
		{
			idx1 = j;
			left1 = ivec[j];
		}
	}
	leftSum = min(leftSum, left1 + left2);

	////  
	idx1 = ivec.size() - 2, idx2 = idx1 - 2; 
	int rightSum = INT_MAX, right1 = ivec[idx1], right2 = ivec[idx2];
	
	for (int i = idx2 - 1; i >= 1; i--)
	{
		if (ivec[i] <= right2)
		{
			idx2 = i;
			right2 = ivec[i];
		}
	}

	for (int j = idx1 - 1; j >= idx2 + 2; j--)
	{
		if (ivec[j] <= right1)
		{
			idx1 = j;
			right1 = ivec[j];
		}
	}

	rightSum = min(rightSum, right1 + right2);

	return min(leftSum, rightSum);
}