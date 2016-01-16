/*
//  https://www.youtube.com/watch?v=m6n_rozU8dA&list=PLTxllHdfUq4f7-uHOpxXnBUbsuLiI9pmb&index=2
//
*/
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

#ifndef HASH_H
#define HASH_H

class hashtable
{
private:
	static const int tablesize = 10;
	
	struct item
	{
		string name;
		string drink;
		item* next;
	};

	item* HashArray[tablesize];

public:
	hashtable();
	int Hash(string key);	// given a key, generate an index for the key to be put in the HashArray
	void AddItem(string name, string drink);   // add new items into HashArray
	int NumberOfItemsInIndex(int index);
	void PrintTable();
};

#endif