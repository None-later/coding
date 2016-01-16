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

int* create1DArray()
{
	int arr[10][10];
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; j++)
		{
			arr[i][j] = 8;
		}
	}
	return arr;
}



int main() 
{
	int arr[8] = { 1, 1, 0, 1, 0, 0, 1, 1 };
	vector<int> ivec(arr, arr+8);
	//priority_queue<int> heap (arr, arr+5);   // max heap
	//priority_queue<int, vector<int>, greater<int> > heap(arr, arr+5); 
	
	int* arrPt = create1DArray(); // size 

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; ++j)

			cout << *(*(arrPt+i) + j) << endl;
		//cout << *arr << endl;
	}




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