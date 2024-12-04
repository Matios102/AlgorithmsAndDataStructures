#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Given a permutation P of the set {1,...,n}, compute the number of pairs (i, j) such that 1 <= i <= j and P[i] > P[j] (such a pair is called an inversion in P).

// Input
// The first line contains integer z (1 <= z <= 2*10^9) - the number of data sets.
// Each data set is as follows:
// The first line contains the number n (1 <= n <= 10000) denoting the size of the permutation P.
// The second line contains n consecutive entries of the permutation P, separated by a space.

// Output
// The number of inversions in P.

class Node
{
	public:
		Node *left;
		Node *right;
		int val;
		int right_count;

	

};


class BstTree
{
	public:
		Node* root;
		int inversions;

		BstTree()
		{
			root = NULL;
			inversions = 0;
		};
		void bstInsert(int _val);
		~BstTree();
		void deleteNode(Node*);
};

BstTree::~BstTree()
{
	deleteNode(root);
}

void BstTree::deleteNode(Node* curr)
{
	if (curr!=NULL)
	{
		deleteNode(curr->left);
		deleteNode(curr->right);
		delete curr;
	}
}

void BstTree::bstInsert(int _val)
{
	Node* curr = new Node();
	curr->val = _val;
	curr->right_count = 0;
	curr->left = NULL;
	curr->right = NULL;
	if (root == NULL)
	{
		root = curr;
		return;
	}
	else
	{
		Node * prev = NULL;
		Node* temp = root;
		bool leftChild = false;
		while( temp != NULL)
		{
			if (_val <= temp->val)
			{
				inversions += temp->right_count + 1;
				prev = temp;
				temp = temp->left;
				leftChild = true;
			}
			else
			{
				temp->right_count++;
				prev = temp;
				temp = temp->right;
				leftChild = false;
			}
		}

		if (leftChild)
			prev -> left = curr;
		else
			prev -> right = curr;
		return;
	}
}

int compute(vector<int>& perm, int n)
{
	BstTree tree = BstTree();

	for(int i = 0; i < n; i++)
		tree.bstInsert(perm[i]);

	return tree.inversions;
}


int main()
{
	vector<int> perm; 
	
	int z,n,m;
	cin >> z;
	while(z)
	{
		perm.clear();		
		cin >> n;
		for(int i=0; i<n; i++)
		{
			int x;
			cin >> x;
			perm.push_back(x);
		}
		int sol = compute(perm, n);
		cout << sol <<"\n";
		z--;
	}
	return 1;
}
