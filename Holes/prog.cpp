#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// You take part in a single-player game.
// At the beginning your pawn is placed in the first field of a one-dimensional board consisting of n fields enumerated from 1 to n.
// Some fields of this board, except the first 1 and the last n, may contain a hole.
// You roll a standard (with six sides) dice and move your pawn toward the last field by the number of dots seen on the dice.
// You lose if you fell into a hole or jumped over field n. You win if you moved the pawn to field n.
// Write a program that counts the number of sequences of dice rolls that lead to your win. 

// Input
// The first line contains integer z (1 <= z <= 2*10^9) - the number of data sets.
// Each dat set is as follows:
// The first line contains the number n (1 <= n <= 10000) denoting the size of the board and the number m (1 ≤ m < 10000).
// The second line contains n numbers from the set {0, 1}, separated by space, determining whether the subsequent fields of the board contain a hole (denoted by 0).

// Output
// The number of sequences of dice rolls that lead to the win (taken modulo m).

 void printVector(vector<int>& v)
 {
	for (int i=0; i<v.size(); i++)
	{
		cout << v[i]<<" ";
	}
	cout <<"\n";	
 }

int compute(vector<int>& board, int n, int m)
{
	vector<int> dp (n+1, 0);
    dp[0] = 1;

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= 6 && i - j >= 0; j++)
        {
            if(board[i - j] == 1)
            {
                dp[i] = (dp[i] + dp[i - j])%m;
            }
        }
    }
	return dp[n - 1]%m;
}

int main()
{
	vector<int> board; 
	
	int z,n,m;
	cin >> z;
	while(z)
	{
		board.clear();		
		cin >> n >> m;
		for(int i=0; i<n; i++)
		{
			int x;
			cin >> x;
			board.push_back(x);
		}
		int sol = compute(board, n, m);
		cout << sol <<"\n";
		z--;
	}
	return 1;
}