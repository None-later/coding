#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

template<typename T>
class MyContainer
{
private:
	std::unordered_map<T, size_t> map;   // item, index
	std::vector<T> vec;					// items

public:
	void Insert(const T& obj)
	{
		vec.push_back(obj);
		map[obj] = vec.size() - 1;
	}
	void Delete(const T& obj)
	{
		// swap the delete item with the last item in the vector
		vec[map[obj]] = vec[vec.size()-1];
		map[vec[vec.size()-1]] = map[obj];
		
		vec[vec.size()-1] = obj;
		vec.pop_back();
		map.erase(obj);
	}
	T& Access(const T& obj)
	{
		return vec[map[obj]];
	}

	int size()
	{
		return vec.size();
	}
	T& operator[](size_t i)
	{
		return vec[i];
	}
};


int main() 
{
	MyContainer<char> container1;

	container1.Insert('a');
	container1.Insert('b');
	container1.Insert('c');
	container1.Insert('d');
	container1.Insert('e');

	container1.Access('e') = 'f';
	container1.Delete('b');

	for (int i = 0; i < container1.size(); ++i)
	{
		cout << container1[i] << endl;
	}




	int arr[8] = { 1, 1, 0, 1, 0, 0, 1, 1 };
	vector<int> ivec(arr, arr+8);
	//priority_queue<int> heap (arr, arr+5);   // max heap
	//priority_queue<int, vector<int>, greater<int> > heap(arr, arr+5); 
	
	//int* arrPt = create1DArray(); // size 

	//for (int i = 0; i < 10; i++)
	//{
	//	for (int j = 0; j < 10; ++j)
	
	//		cout << *(*(arrPt+i) + j) << endl;
	//	//cout << *arr << endl;
	//}

	int m = 4; 
	int n = 5;
	int** arr2D = create2DArray(m, n);

	// print the data
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << arr2D[i][j] << " ";
		}
		cout << endl;;
	}

	// clean up memory
	for (int i = 0; i < m; i++)
	{
		delete [] arr2D[i];
	}
	delete [] arr2D;





	/////////////////////////////////////////
	//int a = 5;
	//int b = 3;

	//int *pt1 = &a;
	//int *pt2 = &b;

	//cout << &a << endl;

	//cout << "pt1 points to : " << static_cast<void*>(pt1) << "the value is " << *pt1 << endl;
	//cout << "pt2 points to : " << static_cast<void*>(pt2) << "the value is " << *pt2 << endl;
	//
	//swap(pt1,pt2);
	//
	//cout << "pt1 points to : " << static_cast<void*>(pt1) << "the value is " << *pt1 << endl;
	//cout << "pt2 points to : " << static_cast<void*>(pt2) << "the value is " << *pt2 << endl;
	//



	//cout << FlipCoin(ivec) << endl;



	getchar();
	return 0;
}