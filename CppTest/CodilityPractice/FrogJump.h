#include <set>

int solution (int A[], int N, int X, int D)
{
	if (D >= X)
		return 0;
	int farthest = 3;
	int currPos = 0;
	std::set<int> connection;
	connection.insert(X);
	for (int i = 0; i < N; ++i)
	{
		if (A[i] > currPos)
		{
			// can be reached 
			if (currPos + D >= A[i])
			{
				currPos = A[i];
				for (auto it = connection.begin(); it != connection.end(); ++it)
				{
					// search connection
					if (*it <= currPos + D)
					{
						currPos = *it;
					}
					else // rm the position that has been reached if there is any
					{
						connection.erase(connection.begin(), it);
					}
				}
			}
			else // can't be reached, add to connections for reaching in the future
			{
				connection.insert(A[i]);
			}
		}
		if (currPos == X)
			return i;
	}
}	