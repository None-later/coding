#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
void printItems(const vector<T> &vec)
{
	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}


int main() 
{
	vector<int> ivec(10);
	vector<short> svec(5);
	svec.assign(6, 10);
	ivec.assign(10, 1);
	printItems(svec);
	svec.assign(ivec.begin(), ivec.end());
	printItems(svec);

	return 0;
}