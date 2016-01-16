#include <cstdlib>
#include <iostream>
#include <string>

#include "hash.h"

using namespace std;

hashtable::hashtable()
{
	// initialize hash array
	for (int i = 0; i < tablesize; ++i)
	{
		HashArray[i] = new item;
		HashArray[i]->name = "empty";
		HashArray[i]->drink = "empty";
		HashArray[i]->next = NULL;
	}
}

void hashtable::AddItem(string name, string drink)
{
	int index = Hash(name);
	
	if (HashArray[index]->name == "empty")
	{
		HashArray[index]->name = name;
		HashArray[index]->drink = drink;
	}
	else
	{
		item* ptr = HashArray[index];
		item* n = new item;
		n->name = name;
		n->drink = drink;
		n->next = NULL;
		while(ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = n;
	}
}

int hashtable::NumberOfItemsInIndex(int index)
{
	int count = 0;
	if (HashArray[index]->name == "empty")
	{
		return count;	// return 0
	}
	else
	{
		++count;
		item* ptr = HashArray[index];
		while(ptr->next != NULL)
		{
			++count;
			ptr = ptr->next;
		}
		return count;
	}
}

void hashtable::PrintTable()
{
	int number;
	for (int i = 0; i < tablesize; ++i)
	{
		number = NumberOfItemsInIndex(i);
		cout << "--------------------\n";
		cout << "index = " << i << endl;
		cout << HashArray[i]->name << endl;
		cout << HashArray[i]->drink << endl;
		cout << "# of items = " << number << endl;
		cout << "--------------------\n";
	}
}

int hashtable::Hash(string key)
{
	int hash = 0;
	int index;

	for (int i = 0; i < key.length(); ++i)
	{
		hash = hash + (int)key[i];
	}
	index = hash % tablesize;

	return index;
}