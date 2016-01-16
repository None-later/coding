/*
 * ContactList.h
 *	
 * Source code from : https://www.youtube.com/watch?v=7vZo17iv1zQ
 */

#include "ContactList.h"

using namespace std;

int main() 
{
	ContactList* cl1 = new ContactList();

	string name;

	while(true)
	{
		cout << "Enter the name of the contact or q to quit." << endl;
		cin >> name;
		if (name =="q")
			break;
		cl1->insert(name);
	}
	while(true)
	{
		cout << "Enter the name of the contact to delete" << endl;
		cin >> name;
		if (name == "q")
			break;
		cl1->deleteNode(name);
	}

	cl1->printList();
	int a;
	cin >> a ;
}