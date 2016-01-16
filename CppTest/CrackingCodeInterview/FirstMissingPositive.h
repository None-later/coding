#include <vector>
#include <set>

using namespace std;
/*
    1. go through the array, for each number in the array, make sure the number is placed on the right position. i.e. 3 should be put on A[2]. If the number is not right swap the numbers to the right position. 
    
correct number in place:  1   2   3    4   5   6       
initial array             3   4   4   -1   1   7
i = 0, swap(A[0], A[2])   4   4   3   -1   1   7               
        swap(A[0], A[3])  -1   4   3    4   1   7   A[0] < 0, skip 
i = 1,                                             A[1] == A[3], skip        
i = 2,                                             A[2] == 3, skip                 
i = 3,                                             A[3] == 4, skip
i = 4, swap(A[0], A[4])   1   4   3    4  -1   7   A[4] < 0 skip
i = 5,                                             A[5] > 6 skip
*/
int firstMissingPositive(vector<int> A) 
{
    if (A.empty())
        return 1;
        
    for (size_t i = 0; i < A.size(); ++i)
    {
        while(A[i] > 0 && A[i] <= A.size() 
            && A[i] != i+1)
        {
            // need to put A[i] to the right place, i.e. A[i]-1
            int tmp = A[A[i]-1];
            if (tmp == A[i])
                break;      // avoid infinitely swaping                
            A[A[i]-1] = A[i];
            A[i] = tmp;
        }
    }
        
    for (size_t i = 0; i < A.size(); ++i)
    {
        if (A[i] != i+1)
            return i+1;
    }
    return A.size()+1;
}