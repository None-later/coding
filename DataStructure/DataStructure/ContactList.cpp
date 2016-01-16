/*
 * ContactList.h
 *	
 * Source code from : https://www.youtube.com/watch?v=7vZo17iv1zQ
 */

#include "ContactList.h"

using namespace std;

ContactList::ContactList(): head(0), size(0)
{}

void ContactList::addToHead(const string& name)
{
	Contact* newOne = new Contact(name);
	if (head == 0)
	{
		head = newOne;
	}
	else
	{
		newOne->next = head;
		head = newOne;
	}
	++size;
}
void ContactList::printList()
{
	Contact* tp = head;	// traverse pointer
	while(tp != 0)
	{
		cout << *tp << endl;
		tp = tp->next;
	}
}
void ContactList::insert(const string& name)
{
	Contact* newNode = new Contact(name);
	// case 1 : insert to empty list
	if (head == 0)
	{
		head = newNode;
	}
	else 
	{
		Contact* curr = head;
		Contact* trail = 0;
		// find the location to insert
		while (curr != 0)
		{
			if (curr->name > newNode->name)
			{
				break;
			}	
			else
			{
				trail = curr;
				curr = curr->next;
			}
		} 
		if (curr == head) 	// case 2 : insert at head 
		{
			newNode->next = curr;
			head = newNode;
		}
		else 	// case 3 : inserrt in between 
		{
			newNode->next = curr;
			trail->next = newNode;
		}
		++size;
	}
}
void ContactList::deleteNode(const string& name)
{
	if (head == 0)
		cout << "Can't delete a node form a empty list" << endl;
	else
	{
		Contact* curr = head;  
		Contact* trail = 0;
		while (curr != 0)
		{
			if (curr->name == name)
				break;	// found the node
			else
			{
				trail = curr;
				curr = curr->next;
			}
		}
		if (curr == 0)
		{
			cout << "Can't find the node in list" << endl;
		}
		else
		{
			// the node is at head
			if (curr == head)
			{
				head = head->next;
			}	
			// the node is beyond the head
			else
			{
				trail->next = curr->next;
			}
			delete curr;
			--size;
		}
	}
}
void ContactList::reversePrintList()
{
	reversePrintWorker(head);
}
void ContactList::reversePrintWorker(Contact* curr)
{
	if (curr != 0)
	{
		reversePrintWorker(curr->next);
		cout << *curr << endl;
	}
}
