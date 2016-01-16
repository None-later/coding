#include <iostream>
#include <cstdlib>
#include "BST.h"

using namespace std;

BST::BST() 
{
	root = NULL;
}

BST::node* BST::CreateLeaf(int key)
{
	node* n = new node;
	n->key = key;
	n->left = NULL;
	n->right = NULL;
	return n;
}
void BST::AddLeaf(int key)
{
	AddLeafPrivate(key, root);   // worker function
}
void BST::AddLeafPrivate(int key, node* pNode)
{
	if (root == NULL)
	{
		root = CreateLeaf(key);
	}
	else if (key < pNode->key)  // go to left
	{
		if (pNode->left != NULL)
		{
			AddLeafPrivate(key, pNode->left);
		}
		else
		{
			pNode->left = CreateLeaf(key);
		}
	}
	else if (key > pNode->key)  // go to right
	{
		if (pNode->right != NULL)
		{
			AddLeafPrivate(key, pNode->right);
		}
		else
		{
			pNode->right = CreateLeaf(key);
		}
	}
	else  // key == pNode->key
	{
		cout << "The key: " << key << "has already been added to the tree\n";
	}
}
void BST::PrintInorder()
{
	PrintInorderPrivate(root);
}
void BST::PrintInorderPrivate(node* pNode)
{
	if (pNode != NULL)
	{
		if (pNode->left != NULL)	
		{
			PrintInorderPrivate(pNode->left);
		}
		cout << pNode->key << " ";
		if (pNode->right != NULL)
		{
			PrintInorderPrivate(pNode->right);
		}
	}
	else
	{
		cout << "The tree is empty\n";
	}
}
BST::node* BST::ReturnNode(int key)
{
	return ReturnNodePrivate(key, root);
}
BST::node* BST::ReturnNodePrivate(int key, node* pNode)
{
	if (pNode != NULL)
	{
		if (pNode->key == key)
		{
			return pNode;
		}
		else 
		{
			if (key < pNode->key)  // got to left
			{
				return ReturnNodePrivate(key, pNode->left);
			}
			else // got to right
			{
				return ReturnNodePrivate(key, pNode->right);
			}
		}
	}
	else
	{
		return NULL;
	}
}
int BST::ReturnRootKey()
{
	if (root != NULL)
		return root->key;
	else
		return -1000;    // assume all numbers in the tree are positive
}
void BST::PrintChildren(int key)
{
	node* pNode = ReturnNode(key);
	if (pNode != NULL)
	{
		cout << "Parent Node = " << pNode->key << endl;
		
		(pNode->left == NULL) ? 
		cout << "Left Child = NULL" << endl :
		cout << "Left Child = " << pNode->left->key << endl;

		(pNode->right == NULL) ? 
		cout << "Right Child = NULL" << endl :
		cout << "Right Child = " << pNode->right->key << endl;
	}
	else
	{
		cout << "Key " << key << "is not in the tree\n";
	}
}
int BST::FindSmallest()
{
	return FindSmallestPrivate(root);
}
int BST::FindSmallestPrivate(node* pNode)
{
	if (root == NULL)
	{
		cout << "The tree is empty\n";
		return -1000;
	}
	else
	{
		if (pNode->left != NULL)
		{
			return FindSmallestPrivate(pNode->left);
		}
		else
		{
			return pNode->key;
		}
	}
}
void BST::RemoveNode(int key)
{
	RemoveNodePrivate(key, root);
}
void BST::RemoveNodePrivate(int key, node* parent)
{
	if (root != NULL)
	{
		if (root->key == key)
		{
			RemoveRootMatch();
		}
		else
		{
			if (key < parent->key && parent->left != NULL)
			{
				parent->left->key == key ?
				RemoveMatch(parent, parent->left, true) :
				RemoveNodePrivate(key, parent->left);
			}
			else if (key > parent->key && parent->right != NULL)
			{
				parent->right->key == key ?
				RemoveMatch(parent, parent->right, false) :
				RemoveNodePrivate(key, parent->right);
			}
			else
			{
				cout << "The key " << key << " was not found in the tree\n";
			}
		}
	}
	else
	{
		cout << "The tree is empty\n";
	}
}
void BST::RemoveRootMatch()
{
	if (root != NULL)
	{
		node* delPtr = root;
		int rootKey = root->key;
		int smallestInRightSubtree;
		// case 0 : root has no child
		if (root->left == NULL && root->right == NULL)
		{
			root = NULL;
			delete delPtr;
		}
		// case 1 : root has one child
		else if (root->left == NULL && root->right != NULL)
		{
			root = root->right;
			root->right = NULL;
			delete delPtr;
			cout << "The root node with key " << rootKey << " was deleted. " 
				 << "The new root contains key " << root->key << endl;

		}
		else if (root->left != NULL && root->right == NULL)
		{
			root = root->left;
			root->left = NULL;
			delete delPtr;
			cout << "The root node with key " << rootKey << " was deleted. " 
				 << "The new root contains key " << root->key << endl;
		}
		// case 2 : root has two children
		else 
		{
			smallestInRightSubtree = FindSmallestPrivate(root->right);
			RemoveNodePrivate(smallestInRightSubtree, root);
			root->key = smallestInRightSubtree;
			cout << "The root key containing key " << rootKey << " was overwritten with key " 
				 << root->key << endl;
		}
	}
	else
	{
		cout << "Can not remove root. The tree is empty\n";
	}
}
