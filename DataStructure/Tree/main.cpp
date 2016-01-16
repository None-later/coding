#include <iostream>
#include <cstdlib>

#include "BST.h"

using namespace std;

int main () 
{
	int TreeKeys[16] = {50, 76, 21, 4, 32, 64, 15, 52, 14, 100, 83, 2, 3, 70, 87, 80};
	BST myTree;
	
	cout << "Printing the tree in order \nBefore adding number\n";
	myTree.PrintInorder();

	for (int i = 0; i < 16; ++i)
	{
		myTree.AddLeaf(TreeKeys[i]);
	}
	
	cout << "Printing the tree in order \nAfter adding number\n";
	myTree.PrintInorder();

	cout << endl;
	
	//for (int i = 0; i < 16; ++i)
	//{
	//	myTree.PrintChildren(TreeKeys[i]);
	//}
	//myTree.PrintChildren(myTree.ReturnRootKey());

	cout << "The smallest value in the tree is " << myTree.FindSmallest() << endl;

	return 0;
}