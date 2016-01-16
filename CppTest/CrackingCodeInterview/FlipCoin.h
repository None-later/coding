#include <vector>

using namespace std;

int FlipCoin(vector<int> coins)
{
	// cond_0 : 0000, all coins are the smae side --> -1
	// cond_1 : 0011, no effect on pairs --> +0
	// cond_2 : 1000, +1
	// cond_3 : 0101, has a hole, +2
	
	
	if (coins.size() < 2)
		return 0;
	if (coins.size() == 2)
		return (coins[0] != coins[1]) ? 1 : 0;

	// check how many adjacency in the original coins
	int pairs = 0;
	for (int i = 1; i < coins.size(); i++)
	{
		if (coins[i] == coins[i-1])
			pairs++;
	}

	int cond = -1;
	for (int i = 1; i < coins.size()-1; i++)
	{
		if (coins[i] != coins[i-1] && coins[i] != coins[i+1])
		{
			cond = 2;
			break;			// already found the best way to maximize the pairs	
		}
		if ((1 == i && coins[i] != coins[i-1]) ||  // 100... or 011...
			(i = coins.size()-2 && coins[i] != coins[i+1]))    // ...001 or ...110
		{
			cond = 1;
		}
		if (coins[i] != coins[i-1])
		{
			cond = (cond == -1) ? 0 : cond;
		}
	}
	return pairs + cond;
}