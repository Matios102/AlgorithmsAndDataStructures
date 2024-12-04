#include<iostream>
#include<iomanip>
#include<algorithm>
#include <vector>
#include <cstdio>
#include <time.h>
#include <math.h>
using namespace std;

// Alice and Bob share a pizza. The pizza is sliced by cuts from the middle to the crust.
// There may be any number of pieces which may be of various sizes. To eat the pizza Alice and Bob have to stick to the following rules:
// • They pick pieces in an alternating fashion,
// • Alice starts by eating any piece of the pizza,
// • Afterward only pieces adjacent to already eaten pieces may be picked.
// Compute the total size of the slices eaten by Alice when both Alice and Bob play their best strategies.

// Input
// The first line contains an integer z (1 <= z <= 2*10^9) - the number of data sets. Each data set is as follows:
// The first line contains a number n - the number of slices (1 <= n <= 4000000). 
// The next line contains n integers denoting the sizes of the consecutive slices, separated by a space.

const int MAX = 4000000;
//int sizeSlize[MAX];
//int gain[MAX][MAX];
//int sumSize[MAX][MAX];

void printTable(int ** A, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j=0; j<n; j++)
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	cout << "******************************\n";
}

void allocate_memory_for_matrix(int** &A, int n)
{
	A =new int * [n];
	for(int i=0; i<n; i++)
	{
		A[i] = new int[n];
	}		
}

void free_memory_for_matrix(int** A, int n)
{
	for (int i=0;i<n;i++)
    delete [] A[i];
	delete [] A;
}


/*
 computes the sum of sizes of slices in the range [i:j]
 sum[i,j]: contains s[i] + s[(i+1) % n] + ... + s[(i+k) %n], where k is such that (i+k)%n = j
*/
void computeSumSize(int * s, int ** sum, int n)
{
	
	for (int i =0; i<n; i++)
	{
		sum[i][i] = s[i];
	}
	
	for(int num = 1; num < n; num++ )
	{
		for (int i = 0; i < n; i++)
		{
			sum[i][(i+num)%n] = sum[i][(i+num-1)%n] + s[(i+num)%n];
		}
	}
}

// computes the gain of the player when the slices left are in the range [i:j]
void computeGain(int* s, int** sum, int **gain , int n)
{
	for(int i = 0; i < n; i++)
    {
        gain[i][i] = s[i];
    }

    for(int num = 1; num < n; num++)
    {
        for(int i = 0; i < n; i++)
        {
			// Player has two choices: take the left slice or the right slice
			// Taking the left slice means that the other player will have the maximum gain from the slices [i+1:j]
            int left = sum[i][(i+num)%n] - gain[(i+1)%n][(i+num)%n];
			
			// Taking the right slice means that the other player will have the maximum gain from the slices [i:j-1]
            int right = sum[i][(i+num)%n] - gain[i][(i + num - 1)%n];

			// The player will choose the slice that gives him the maximum gain
            gain[i][(i+num)%n] = max(left, right);
        }
    }
}


int z,n;
int ** sumSize;
int ** FPGain;
int * sliceSize;


int main()
{
	cin >> z;
	while(z)
	{
		cin >> n;
		sliceSize = new int[n];
		allocate_memory_for_matrix(sumSize,n);
		allocate_memory_for_matrix(FPGain,n);
		for(int i=0; i<n; i++)
		{
			cin >> sliceSize[i];
		}
		computeSumSize(sliceSize,sumSize,n);
		computeGain(sliceSize,sumSize,FPGain,n);
		int AliceGain = 0;
		for (int i=0; i < n; i++)
		{
			if (FPGain[i][(i-1)%n] > AliceGain)
				AliceGain = FPGain[i][(i+n-1)%n];
		}
		cout << AliceGain <<"\n";
		free_memory_for_matrix(FPGain,n);
		free_memory_for_matrix(sumSize,n);
		delete [] sliceSize;
		z--;
	}		
}