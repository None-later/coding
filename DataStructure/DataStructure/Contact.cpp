/*
 * Contact.cpp
 *	
 * Source code from : https://www.youtube.com/watch?v=lmpOVPGzN6M
 */

#include "Contact.h"

using namespace std;

Contact::Contact(string n) : name(n), next(NULL)
{}

//overloading insertion operator
ostream& operator<<(ostream& os, const Contact& c)
{
	return os << "Name: " << c.name;
}