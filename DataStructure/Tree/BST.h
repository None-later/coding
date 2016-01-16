class BST 
{
private:
	struct node
	{
		int key;
		node* left;
		node* right;
	};
	node* root;
	void AddLeafPrivate(int key, node* pNode);
	void PrintInorderPrivate(node* pNode);
	node* ReturnNodePrivate(int key, node* pNode);
	int FindSmallestPrivate(node* pNode);
	void RemoveNodePrivate(int key, node* parent);
	void RemoveRootMatch();

public:
	BST();
	node* CreateLeaf(int key);
	void AddLeaf(int key);
	void PrintInorder();
	node* ReturnNode(int key);
	int ReturnRootKey();
	void PrintChildren(int key);
	int FindSmallest();
	void RemoveNode(int key);

};