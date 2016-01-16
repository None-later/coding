/*
 * ContactList.h
 *	
 * Source code from : https://www.youtube.com/watch?v=7vZo17iv1zQ
 */

#ifndef CONTACTLIST_H_
#define CONTACTLIST_H_

#include "Contact.h"

class ContactList
{
public:
	ContactList();
	void addToHead(const std::string&);
	void printList();
	void insert(const std::string&);
	void deleteNode(const std::string&);
	void reversePrintList();				// Wrapper function

private:
	void reversePrintWorker(Contact*);
	Contact* head;
	int size;
};

#endif /* CONTACTLIST_H_ */