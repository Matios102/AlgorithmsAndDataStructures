#include <iostream>
#include <string>
#include <sstream>

using namespace std;
// Implement a binary search tree (BST) with the following operations:
// - INSERT x: insert x into the BST. If x is already in the BST, do nothing.
// - SEARCH x: print 1 if x is in the BST, and 0 otherwise.
// - PREORDER: print the preorder traversal of the BST.
// - INORDER: print the inorder traversal of the BST.
// - POSTORDER: print the postorder traversal of the BST.

// Input
// The first line of the input contains an integer z (1 ≤ z ≤ 1000) — the number of test cases. The description of the test cases follows.
// The first line of each test case contains an integer n (1 ≤ n ≤ 1000) — the number of operations. Each of the following n lines contains an operation in the format described above.

class Node
{
	public:
		Node *left;
		Node *right;
		int val;
        Node(int _val)
        {
            this->val = _val;
            this->right = NULL;
            this->left = NULL;
        }
};


class BstTree
{
	public:
		Node* root;
		BstTree()
		{
			root = NULL;
		};
		void inOrderSeq();	
		void postOrderSeq();
		void preOrderSeq();
		int bstInsert(int _val); // inserts _val to bstTree; returns 1 is _val is added (which may happen only when _val is not in bstTree) and 0 otherwise
		int bstSearch(int _val); // returns 1 if _val is in the bstTree and 0 otherwise
		~BstTree();
	private:
		void inOrder(Node *);
		void postOrder(Node *);
		void preOrder(Node *);
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
		//cout << "Usuwanie noda z kluczem:" << curr ->val << "\n" ;
		delete curr;
	}
}

int BstTree::bstInsert(int _val)
{
	
    if(root == NULL)
    {
        root = new Node(_val);
        return 1;
    }
        
    Node* current = root;
    while(current)
    {
        if(_val > current->val)
        {
            if(current->right == NULL)
            {
                current->right = new Node(_val);
                return 1;
            }
            else
                current = current->right;
        }
            

        else if(_val < current->val)
        {
            if(current->left == NULL)
            {
                current->left = new Node(_val);
                return 1;
            }
            else
                current = current->left;
        }
        

        else
            return 0;
    }
	return 0;
}


int BstTree::bstSearch(int _val)
{
	Node* current = root;
    while(current)
    {
        if(current->val == _val)
            return 1;

        else
        {
            if(_val > current->val)
                current = current->right;
            
            else if(_val < current->val)
                current = current->left;
        }
    }
	return 0;
}



void BstTree::preOrderSeq()
{
	preOrder(root);
}

void BstTree::preOrder(Node * curr)
{
	cout << curr->val << " ";
    if(curr->left != NULL)
        preOrder(curr->left);
    
    if(curr->right != NULL)
        preOrder(curr->right);
}

void BstTree::inOrderSeq()
{
	inOrder(root);
}

void BstTree::inOrder(Node * curr)
{
	if(curr->left != NULL)
        inOrder(curr->left);

    cout << curr->val << " ";

    if(curr->right != NULL)
        inOrder(curr->right);
}

void BstTree::postOrderSeq()
{
	postOrder(root);
}

void BstTree::postOrder(Node * curr)
{
	if(curr->left != NULL)
        postOrder(curr->left);

    if(curr->right != NULL)
        postOrder(curr->right);

    cout << curr->val << " ";
}


int main()
{
	int z,n;
	string zstr,nstr;
	getline(cin, zstr);
	istringstream(zstr) >> z;
	while(z)
	{
		getline(cin, nstr);
		istringstream(nstr) >> n;
		BstTree bstTree = BstTree();
		for (int i=0; i<n;i++)
		{
			string line;
			getline(cin, line);
			string instr;
			int num;
			istringstream(line) >> instr >> num;
			if (instr == "INSERT")
				cout << bstTree.bstInsert(num) << "\n";
			else if (instr == "SEARCH")
				cout << bstTree.bstSearch(num)<<"\n";
			else if (instr == "PREORDER")
			{
				bstTree.preOrderSeq();
				cout <<"\n";
			}
			else if (instr == "INORDER")
			{
				bstTree.inOrderSeq();
				cout <<"\n";
			}
			else if (instr == "POSTORDER")
			{
				bstTree.postOrderSeq();
				cout <<"\n";
			}			
		}
		z--;
	}	
}
