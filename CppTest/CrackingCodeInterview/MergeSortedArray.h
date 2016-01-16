#include<vector>

using namespace std;

void mergeSortedArray(int A[], int m, int B[], int n) 
{
	int end = m + n - 1;
	int end1 = m - 1;
	int end2 = n - 1;
	while (end1 >= 0 && end2 >= 0)
		A[end--] = (A[end1] > B[end2]) ? A[end1--] : B[end2--];
	while (end1 >= 0)
		A[end--] = A[end1--];
	while (end2 >= 0)
		A[end--] = B[end2--];	
}