#include <vector>

std::vector<int> solution2(int N, std::vector<int> &A) 
{
    std::vector<int> res(N,0);
    int currMax = 0;
    for (int i = 0; i < A.size(); ++i)
    {
        if (A[i] == N+1)
        {
            for (int j = 0; i < res.size(); ++j)
            {
                res[j] = currMax;    
            }
        }
        else
        {
            res[A[i]-1]++;
            if (res[A[i]-1] > currMax)
                currMax = res[A[i]-1];
        }
    }
    return res;
}