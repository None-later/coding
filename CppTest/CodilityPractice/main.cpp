#include <iostream>
#include <vector>

#include "FrogJump.h"
#include "NumberSolitaire.h"
#include "Real_ParitionThree.h"
#include "Real_StackOperation.h"

using namespace std;

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

	

	//char s[] = "13+62*7";
	

	cout << StackOperation("13+62*7+*") << endl;

	getchar();
	return 0;
}
