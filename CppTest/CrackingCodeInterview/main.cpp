#include <iostream>
#include "ArrayAndString.h"
#include "FirstMissingPositive.h"
#include "WoodCut.h"
#include "StringToInt.h"
#include "ReverseWordsInString.h"
#include "RemoveLinkedListNode.h"
#include "Int2Roman.h"
#include "FlipCoin.h"

#include <vector>
#include <queue>
#include <functional>
#include <string>
#include <unordered_map>
using namespace std;

int findch(const char *s, char ch)
{
	int found;
	while(s)
	{
		if (*s == ch)
			found =1;
	}
	++s;
	return found;
}

// swap two pointers
void swap(int*& p1, int*& p2)
{
	int* temp = p1; 
	p1 = p2;
	p2 = temp;
}

// function that return 2D array
int** create2DArray(unsigned rows, unsigned columns)
{
	int** array2D = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		array2D[i] = new int[columns];
		for (int j = 0; j < columns; j++)
		{
			array2D[i][j] = i * j;
		}
	}
	return array2D;
}

template<typename T>
class MyContainer
{
private:
	std::unordered_map<T, size_t> map;   // item, index
	std::vector<T> vec;					// items
	int size = 0;
public:
	void Insert(const T& obj)
	{
		vec.push_back(obj);
		map[obj] = size++;
	}
	void Delete(T obj)
	{
		if (size != 0)
		{
			size_t del = map[obj];
			size_t end = vec.size() - 1;
			// swap the delete item with the last item in the vector
			vec[del] = vec[end];
			vec[end] = obj;
			vec.pop_back();
			
		}
	}
	T& Modify(T obj)
	{
		
	}
}




int main() 
{
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