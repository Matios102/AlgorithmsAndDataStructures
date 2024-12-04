#include<iostream>
#include<iomanip>
#include<algorithm>
#include <vector>
#include <cstdio>
#include <time.h>
#include <math.h>
using namespace std;

// for a given sequence of n pairwise distinct integers compute,
// for every 0 <= i <= n - 1, the size of the largest increasing subsequence
// with the last element equal to the i-th element of the sequence.

// Input
// The first line contains an integer z (1 <= z <= 2*10^9) - the number of data sets. 
// An exemplary data set is as follows:
// The first line contains number n denoting the size of the sequence (1 <= n <= 4000000).
// The next line contains n integers of the sequence, separated by a space.

// Output
// Sequence of integers separated by a space. The i-th integer is the size of the largest increasing subsequence with the last element equal to the i-th element of the sequence.


const int MAX = 4000000;
int tab[MAX];
int lis[MAX];
int glob;


void printTable(int * t, int n)
{
	for (int i=0; i<n; i++)
	{
		cout << t[i] << " ";
	}
	cout << endl;
}


void computeLIS(int * t, int * lis, int n)
{
	for(int i = 0; i < n; i++)
    {
        lis[i] = 1;
    }

    for(int i = 1; i < n; i++)
    {
        int longest = lis[i];
        for(int j = i -1; j >= 0; j--)
        {
            if(t[j] < t[i] && lis[j] + 1 > longest)
            {
                longest = lis[j] + 1;
            }
        }
        lis[i] = longest;
    }
}


int main()
{
	int z,n;
	cin >> z;
	while(z)
	{
		cin >> n;
		for(int i=0; i<n; i++)
		{
			cin >> tab[i];
		}
		//printTable(tab,n);
		computeLIS(tab,lis,n);
		printTable(lis,n);
		z--;
	}
		
}
