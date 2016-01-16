#include <iostream>
#include <cstdlib>

#include "QueueTemplate.h"

template<typename T> ostream& operator<<(ostream &os, const Queue<T> &q)
{
	
}



template<typename T> void Queue<T>::destroy()
{
	while(!empty())
		pop();
}
template<typename T> void Queue<T>::pop()
{
	QueueItem<T>* p = head;   // wait to be deleted 
	head = head->next;
	delete p;
}
template<typename T> void Queue<T>::push(const T& val)
{
	QueueItem<T>* newItem = new QueueItem<T>(val);
	if (empty())
		head = tail = newItem;		// only one item in Queue
	else
		tail->next = newItem;		// add new item to the back
}
template<typename T> void Queue<T>::copy_elems(const Queue<T>& q)
{
	// copy each item in q to the current Queue
	// while pt != 0 (null), keep copying ... 
	for (QueueItem<T> *pt = q.head; pt; pt = pt->next)
		push(pt->item);
}
// practive member template to convert different types between templates, pg. 661
template<typename T> template<typename Iter> void Queue<T>::assign(Iter beg, Iter end)
{
	destroy();
	copy_elems(beg, end);
}
//template<typename T> template<typename Iter> void