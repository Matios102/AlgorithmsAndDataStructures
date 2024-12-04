#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// Your task is to write a program which recovers a binary tree from two different traversal orders among PREORDER, INORDER, POSTORDER. 
// Assume the keys are positive integers; we reserve O to denote the NULL pointers, which are also outputted by each traversal. 

// Input
// The first line contains integer z (1 <= z <= 2*10^9) - the number of data sets. 
// Each data set is as tollows:
// The first line contains the names of two different traversal orders and the number n denoting the size of each order. 
// The second and the third line contain the sequence of n integers of the first and the second traversal, respectively.

//Output
//You should output the sequence of n integers of the third traversal (distinct from the
//first and the second one).

using namespace std;

class Node
{
    public:
        Node *left;
        Node *right;
        int val;
};


class BinaryTree
{
    public:
        Node* root;
        BinaryTree()
        {
            root = NULL;
        };
        BinaryTree(string fO, string sO, vector<int>* firstOrder, vector<int>* secondOrder, int n);
        void inOrderSeq();
        void postOrderSeq();
        void preOrderSeq();
        ~BinaryTree();
    private:
        void inOrder(Node *);
        void postOrder(Node *);
        void preOrder(Node *);
        void deleteNode(Node*);
        Node* prein(vector<int>* firstOrder, vector<int>* secondOrder, int preOrderL, int inOrderL, int size);
        Node* inpost(vector<int>* firstOrder, vector<int>* secondOrder, int inOrderL, int postOrderL, int size);
        Node* prepost(vector<int>* preOrder, vector<int>* postOrder, int preOrderL, int postOrderL, int size);
};

BinaryTree::~BinaryTree()
{
    deleteNode(root);
}

void BinaryTree::deleteNode(Node* curr)
{
    if (curr!=NULL)
    {
        deleteNode(curr->left);
        deleteNode(curr->right);
        delete curr;
    }
}


BinaryTree::BinaryTree(string firstOrderName, string secondOrderName, vector<int>* firstOrder, vector<int>* secondOrder, int n)
{
    if ((firstOrderName=="PREORDER") && (secondOrderName=="INORDER"))
    {
        root = prein(firstOrder, secondOrder,0,0,n);
        return;
    }
    if ((firstOrderName=="INORDER") && (secondOrderName=="POSTORDER"))
    {
        root = inpost(firstOrder, secondOrder,0,0,n);
        return;
    }
    if ((firstOrderName=="PREORDER") && (secondOrderName=="POSTORDER"))
    {
        root = prepost(firstOrder, secondOrder,0,0,n);
        return;
    }
}

Node* BinaryTree::prepost(vector<int>* preOrder, vector<int>* postOrder, int preOrderL, int postOrderL, int size)
{
    if (size <= 1)
        return NULL;

    int val = (*preOrder)[preOrderL];
    Node* root = new Node();
    root->val = val;
    int leftChildPos;
    for (int i = postOrderL; i < postOrderL + size; i++)
    {
        if ((*preOrder)[preOrderL+1] == (*postOrder)[i])
        {
            leftChildPos = i;
            break;
        }
    }
    int leftSize = leftChildPos - postOrderL + 1;
    int rightSize = size - leftSize - 1;

    root->left = prepost(preOrder, postOrder, preOrderL+1, postOrderL, leftSize);
    root->right = prepost(preOrder, postOrder, preOrderL+leftSize+1, postOrderL+leftSize, rightSize);
    return root;
}


Node* BinaryTree::prein(vector<int>* preOrder, vector<int>* inOrder, int preOrderL, int inOrderL, int size)
{
    if (size <= 1)
        return NULL;
    
    int val = (*preOrder)[preOrderL];
    Node* root = new Node();
    root->val =val;
    int leftSize;
    int rightSize;
    int rootPos;
    for (int i = inOrderL+1; i < inOrderL+size; i++)
    {
        if ((*inOrder)[i] == val)
        {
            rootPos = i;
            break;
        }
    }
    leftSize = rootPos - inOrderL;
    rightSize = size - leftSize - 1;

    root->left = prein(preOrder, inOrder, preOrderL+1, inOrderL, leftSize);
    root->right = prein(preOrder, inOrder, preOrderL+leftSize+1, rootPos+1, rightSize);
    return root;
}

Node* BinaryTree::inpost(vector<int>* inOrder, vector<int>* postOrder, int inOrderL, int postOrderL, int size)
{
    if (size <= 1)
        return NULL;

    int val = (*postOrder)[postOrderL+size-1];
    Node* root = new Node();
    root->val = val;
    int rootPos;
    for (int i = inOrderL; i < size + inOrderL; i++)
    {
        if ((*inOrder)[i] == val)
        {
            rootPos = i;
            break;
        }
    }
    int leftSize = rootPos - inOrderL;
    int rightSize = size - leftSize - 1;

    root->left = inpost(inOrder, postOrder, inOrderL, postOrderL, leftSize);
    root->right = inpost(inOrder, postOrder, inOrderL+leftSize+1, postOrderL+size-rightSize-1, rightSize);
    return root;
}


void BinaryTree::preOrderSeq()
{
    preOrder(root);
}

void BinaryTree::preOrder(Node * curr)
{
    if (curr == NULL)
    {
        cout <<"0 ";
        return;
    }
    cout << curr->val <<" ";
    preOrder(curr->left);
    preOrder(curr->right);
}

void BinaryTree::inOrderSeq()
{
    inOrder(root);
}

void BinaryTree::inOrder(Node * curr)
{
    if (curr == NULL)
    {
        cout << "0 ";
        return;
    }
    inOrder(curr->left);
    cout << curr->val <<" ";
    inOrder(curr->right);
}

void BinaryTree::postOrderSeq()
{
    postOrder(root);
}

void BinaryTree::postOrder(Node * curr)
{
    if (curr == NULL)
    {
        cout << "0 ";
        return;
    }
    postOrder(curr->left);
    postOrder(curr->right);
    cout << curr->val <<" ";
}

int main()
{
    vector<int> firstOrder;
    vector<int> secondOrder;
    int z;
    string line;
    getline(cin, line);
    istringstream(line) >> z;
    while(z)
    {
        getline(cin, line);
        string firstOrderName,secondOrderName;
        int n;
        istringstream(line) >> firstOrderName >> secondOrderName >> n;
        firstOrder.clear();
        secondOrder.clear();
        getline(cin, line);
        istringstream firstString(line);
        getline(cin, line);
        istringstream secondString(line);
        for(int i =0; i<n; i++)
        {
            int val;
            firstString >> val;
            firstOrder.push_back(val);
            secondString >> val;
            secondOrder.push_back(val);
        }
        
        BinaryTree binTree = BinaryTree(firstOrderName, secondOrderName, &firstOrder, &secondOrder, n);
        //cout << firstOrderName << " " << secondOrderName <<"\n";

        if ((firstOrderName == "PREORDER") && (secondOrderName == "INORDER"))
        {
            binTree.postOrderSeq();
            cout << "\n";
        } else
        if ((firstOrderName == "INORDER") && (secondOrderName == "POSTORDER"))
        {
            binTree.preOrderSeq();
            cout << "\n";
        } else
        if ((firstOrderName == "PREORDER") && (secondOrderName == "POSTORDER"))
        {
            binTree.inOrderSeq();
            cout << "\n";
        }
        z--;
    }
}





