#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Given a sequence S of n weights, calculate the heaviest subsequence of S containing no two adjacent entries.

// Input
// The first line contains integer z (1 <= z <= 2*10^9) - the number of data sets.
// Each data set is as follows:
// The first line contains the number n (1 <= n <= 10000) denoting the size of the sequence S.
// The second line contains the weights w (0 < w < 10000) of n consecutive entries of the sequence, separated by a space.

// Output
// The weight of the heaviest subsequence of S containing no two adjacent entries of S.

 void printVector(vector<int>& v)
 {
	for (int i=0; i<v.size(); i++)
	{
		cout << v[i]<<" ";
	}
	cout <<"\n";	
 }

int compute(vector<int>& seq, int n)
{
	vector<int> res(n);
	res[0] = seq[0];
	if(seq[1] > seq[0])
		res[1] = seq[1];
	
	else
		res[1] = seq[0];
	
	for(int i = 2; i < n; i++)
	{
		if(seq[i] + (res[i-1] - seq[i-1]) > seq[i] + res[i-2])
			res[i] = (res[i -1] - seq[i-1]) + seq[i];

		else
			res[i] = res[i-2] +  seq[i];
	}

	int maxgain = 0;

	for(int i = 0; i < n; i++)
		if(res[i] > maxgain)
			maxgain = res[i];

	return maxgain;
}

int main()
{
	vector<int> seq;	
	int z,n;
	cin >> z;
	while(z)
	{
		seq.clear();		
		cin >> n;
		for(int i=0; i<n; i++)
		{
			int x;
			cin >> x;
			seq.push_back(x);
		}
		int sol = compute(seq, n);
		cout << sol <<"\n";
		z--;
	}
	return 1;
}
