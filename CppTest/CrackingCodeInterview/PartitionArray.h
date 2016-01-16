#include <vector>

/*
//  if (i >= right && nums[i] < k) --> swap !! 

					6	4	3	2	1	5		k = 3 
i = 0, right = 0	res
i = 1. right = 0    res
i = 2, right = 0    res
i = 3, right = 1    2	4   2   6	1	5		swap(2, 6)
						res
i = 4, right = 2	2   1   3   6   4   5		swap(1, 4)
						    res
i = 5, right = 2			res
-----------------------------------------------------------------
					1	2	3	2	4	2		k = 3 
i = 0, right = 0		res						swap (1,1), res++
i = 1, right = 1			res					swap (2,2), res++
i = 2, right = 0			res   
i = 3, right = 1	1	2	2	3	4	2		swap (3,2), res++ 			
								res
i = 4, right = 2				res
i = 5, right = 2	1	2	2	2	4	3		swap (3,2), res++ 						
									res			
*/
int partitionArray(std::vector<int> &nums, int k) 
{
	int right = 0;
	//for (int i = 0; i < nums.size(); ++i)
	//{
	//	if (i >= right && nums[i] < k)
	//	{
	//		int temp = 
	//	}
	//}
	return right;
}