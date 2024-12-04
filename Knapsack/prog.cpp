#include<iostream>
#include<iomanip>
#include<algorithm>
#include <vector>
#include <cstdio>
#include <time.h>
#include <math.h>
using namespace std;

// Given a collection of n items, each having a value and a size, and a knapsack of
// size W choose a set of items from this collection,
// whith total size is <=  W and total value as high as possible.

// Input
// The first line contains an integer z (1 <= z <= 2*10^9) - the number of data sets. Each
// data set is as follows:
// The first line contains number n of items (1 <= n <= 4000000) and size W of the knapsack. 
// The second line contains n integers denoting the sizes of the consecutive items, separated by a space. 
// The third line contains n integers denoting the value of the consecutive items, separated by a space.

// Output
// For each data set, output the maximum value of the items that can be taken in the knapsack.

const int MAX = 4000;
int itemSize[MAX]; 
int itemValue[MAX];

//auxiliary function
void printTable(int ** A, int n, int W)
{
	for (int i = 0; i <= n; i++)
	{
		for (int j=0; j<=W ; j++)
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	cout << "******************************\n";
}

// function allocating memory for amn int table of size (n+1) x (W+1)
void allocate_memory_for_matrix(int** &A, int n, int W)
{
	A = new int* [n+1];
	for(int i=0; i<=n; i++)
	{
		A[i] = new int[W+1];
	}		
}

// function freeing memory taken by a table of size (n+1) x (W+1)
void free_memory_for_matrix(int** A, int n)
{
	for (int i=0;i<=n;i++)
	{
		delete [] A[i];
	}
	delete [] A;
}


void solve(int* s, int * v, int ** A, int n, int W)
{
	
    for(int i = 0; i <= W; i++)
        A[0][i] = 0;

    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j <= W; j++)
        {
            A[i+1][j] = A[i][j];

            if(s[i] <= j && A[i][j] < A[i][j - s[i]] + v[i])
                A[i+1][j] = A[i][j - s[i]] + v[i];
        }
    }
}

int main()
{
	int z,n,W;
	cin >> z;
	while(z)
	{		
		cin >> n >> W;
		int ** tab;
		allocate_memory_for_matrix(tab,n,W);
		for(int i=0; i<n; i++)
		{
			cin >> itemSize[i];
		}
		for(int i=0; i<n; i++)
		{
			cin >> itemValue[i];
		}
		solve(itemSize,itemValue, tab, n, W);
		cout << tab[n][W] << "\n";
		free_memory_for_matrix(tab,n);
		z--;
	}
		
}
