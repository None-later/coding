#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct Node
{
	ElementType Element;
	Position Next;
};
//make an empty list
Position MakeEmpty(List L)
{
	if (L != NULL)
		DeleteList(L);
	L = (List)malloc(sizeof(struct Node));
	L->Next = 0;
	return L;
}
/* Return true if L is empty */
int IsEmpty(List L)
{
	return L->Next == NULL;		
}	
/* Return true if P is the last position in list L */
/* Parameter L is unused in this implementation */
int IsLast(Position P)
{
	return P->Next == NULL;
}
/* Return Position of X in L; NULL if not found */
Position Find(ElementType X, List L)
{
	//if (L->Next == NULL) // List is empty 
	//	return NULL;  // error NULL is not Position !! 
	Position curr = L->Next;
	while (curr != NULL && curr->Element != X)
		curr = curr->Next;
	return curr;
}       
/* Delete from a list */
/* Cell pointed to by P->Next is wiped out */
/* Assume that the position is legal */
/* Assume use of a header node */
void Delete(ElementType X, List L)
{
	Position curr = L->Next;
	if (curr->Element == X)
	{
		Position tmp = curr;
		L->Next = curr->Next;
		free(tmp);
	}
	else
	{
		while(curr->Next != NULL && curr->Next->Element != X)
			curr = curr->Next;
		if (curr->Next->Element)
		{
			Position tmp = curr->Next;
			curr->Next = tmp->Next;
			tmp->Next = NULL;
			free(tmp);
		}
	}
}
/* If X is not found, 
then Next field of returned value is NULL */
Position FindPrevious(ElementType X, List L)
{
	Position curr = L;
	while (curr->Next != NULL && curr->Next->Element != X)
		curr = curr->Next;
	return curr;
}
/* Insert (after legal position P) */
/* Header implementation assumed */
/* Parameter L is unused in this implementation */
void Insert(ElementType X, List L, Position P)
{
	Position newNode = (Position)malloc(sizeof(struct Node));
	newNode->Element = X;
	newNode->Next = P->Next;
	P->Next = newNode;
}
void DeleteList(List L)
{
	Position curr = L->Next;
	L->Next = NULL;          // definition of an empty list : L->Next == NULL 
	while (curr != NULL)
	{
		Position tmp = curr->Next;
		free(curr);
		curr = tmp;
	}
}
Position Header(List L)
{
	return L;
}
Position First(List L)
{
	return L->Next;
}
Position Advance(Position P)
{
	return P->Next;
}
ElementType Retrieve(Position P)
{
	return P->Element;
}
////////////////////////////////////////////////////////////
void Sort(List L)
{
	struct Node* first = L->Next;
	struct Node* second = first->Next;
	while (first->Next != NULL)
	{
		while (second != NULL)
		{
			if (first->Element > second->Element)
			{
				ElementType tmp = first->Element;
				first->Element = second->Element;
				second->Element = tmp;
			}
			second = second->Next;
		}
		first = first->Next;
		second = first->Next;	
	}
}
void InsertToSorted(ElementType X, List L)
{
	//Sort(L);
	Position curr = L->Next;
	while (curr != NULL && curr->Element < X)
	{
		// case 1: curr->Next == NULL, insert to the back of the list
		if (curr->Next == NULL)
		{
			struct Node* tmp = (Position)malloc(sizeof(struct Node));
			tmp->Element = X;
			tmp->Next = NULL;
			curr->Next = tmp;
			break;
		}
		// case 2: insert between curr and curr->next
		if (curr->Next != NULL && curr->Next->Element >= X)  
		{
			Position tmp = (Position)malloc(sizeof(struct Node));
			tmp->Element = X;
			tmp->Next = curr->Next;
			curr->Next = tmp;
			break;
		}
		curr = curr->Next;
	}
}
void ReverseList(List L)
{
	////version 1: my version
	////cannot pass the special case where the list is empty
	//Position curr = L->Next;
	//Position tmp = curr->Next; // when the list is empty, error ! 
	//curr->Next = NULL;
	//while(tmp != NULL)
	//{
	//	Position prev = curr;
	//	curr = tmp;
	//	tmp = curr->Next;
	//	curr->Next = prev;
	//}
	//L->Next = curr;

    // version 2 : online tutorial 
	Position prev = NULL;
	Position curr = L->Next;
	Position tmp;
	while(curr != NULL)
	{
		tmp = curr->Next;   // store curr->next before curr points to prev
		curr->Next = prev;
		prev = curr;
		curr = tmp;
	}
	L->Next = prev;
}
void ReversePrint(Position P)
{
	if (P == NULL)
		return;
	ReversePrint(P->Next);
	printf("%d ", P->Element);
}
// 